%% Advanced Features
% This example shows advanced features such as limits, units and
% calibration.
% 			
% Requires at least one Fluigent pressure controller (MFCS, MFCS-EZ or Flow
% EZ) and/or one Fluigent sensor (Flow Unit connected to FRP or Flow EZ)
%
% <matlab:edit('Fluigent_SDK_AdvancedFeatures') Open this M File>

%% Unit change

pressureIndex = 0;
sensorIndex = 0;

% Read pressure value
pressureValue = fgt_get_pressure(pressureIndex);
pressureUnit = fgt_get_pressureUnit(pressureIndex);
fprintf('Read pressure: %f %s\n', pressureValue, pressureUnit);

% Read sensor value
sensorValue = fgt_get_sensorValue(sensorIndex);
sensorUnit = fgt_get_sensorUnit(sensorIndex);
fprintf('Read sensor: %f %s\n', sensorValue, sensorUnit);

% Change pressure and sensor unit
% Note that if incorrect or invalid unit is used an error is returned.
% When unit is changed, all values are then in set unit
fgt_set_pressureUnit(pressureIndex, 'PSI');
fgt_set_sensorUnit(sensorIndex, 'ulperhour');
fprintf('Changed pressure and sensor unit\n');

% Read pressure value again
pressureValue = fgt_get_pressure(pressureIndex);
pressureUnit = fgt_get_pressureUnit(pressureIndex);
fprintf('Read pressure: %f %s\n', pressureValue, pressureUnit);

% Read sensor value again
sensorValue = fgt_get_sensorValue(sensorIndex);
sensorUnit = fgt_get_sensorUnit(sensorIndex);
fprintf('Read sensor: %f %s\n', sensorValue, sensorUnit);

%% Limit change

[minPressure, maxPressure] = fgt_get_pressureRange(pressureIndex);
fgt_set_pressureLimit(pressureIndex, minPressure / 2, maxPressure / 2);
fprintf('Changed pressure limit to %f - %f\n', minPressure / 2, maxPressure / 2);
fprintf('Trying to set pressure to %f\n', maxPressure);
fgt_set_pressure(pressureIndex, maxPressure);

%% Calibration

% Pressure calibration
fgt_calibratePressure(pressureIndex);
fprintf('Calibrating pressure channel... trying to send pressure order in same time\n');
fgt_set_pressure(pressureIndex, maxPressure/2);
% An error is thrown, set pressure orders are not accepted during calibration

% Sensor calibration
% Read sensor calibration table
sensorCalibration = fgt_get_sensorCalibration(sensorIndex);
fprintf('Read sensor calibration: %s\n', char(sensorCalibration));

% Change sensor calibration to water
% Note that if calibration is not supported, an error is thrown
fgt_set_sensorCalibration(sensorIndex, fgt_SENSOR_CALIBRATION.H2O);
disp('Setting sensor calibration...');
% As for pressure calibration, this step needs a few moments before the
% read values are correct. The same error is thrown.
pause(1)
% Read sensor calibration table again
sensorCalibration = fgt_get_sensorCalibration(sensorIndex);
fprintf('Read sensor calibration: %s\n', char(sensorCalibration));

%% Close the session
fgt_close

%%
% Copyright (c) Fluigent 2019.  All Rights Reserved.