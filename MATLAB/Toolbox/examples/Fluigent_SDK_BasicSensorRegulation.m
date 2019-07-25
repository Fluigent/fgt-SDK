%% Basic Sensor Regulation
% This example shows how to set a sensor regulation and generate a
% sinusoidal profile on the first sensor and pressure module of the chain
% 			
% Requires at least one Fluigent pressure controller (MFCS, MFCS-EZ or
% Flow EZ) and at least one Fluigent sensor (Flow Unit connected to FRP or
% Flow EZ)
%
% <matlab:edit('Fluigent_SDK_BasicSensorRegulation') Open this M File>

%% Initialize the session
% This step is optional, if not called session will be automatically
% created
fgt_init

%% Get sensor range
[minSensor, maxSensor] = fgt_get_sensorRange(0);

%% Read sensor value

sensorMeasurement = fgt_get_sensorValue(0);
fprintf('Current sensor value: %f\n', sensorMeasurement)

%% Start regulation

% Set regulation setpoint to 10% of the maximum sensor value
% Use the first sensor and the first pressure channel detected
fgt_set_sensorRegulation(0, 0, maxSensor/10);

% Wait 5 seconds for the pressure to settle
disp('Waiting 5 seconds...');
pause(5)

% Read sensor value
sensorMeasurement = fgt_get_sensorValue(0);
fprintf('Current sensor value: %f\n', sensorMeasurement);

%% Create a sinusoidal profile 
% The profile oscillates between the minimum and the maximum sensor value

% Create the sine wave setpoints
amplitude = (maxSensor-minSensor);
offset = minSensor;
sinePoints = (sin((0:10:360)*pi/180)+1)/2;
setpoints = sinePoints*amplitude + offset;

for sensorSetpoint = setpoints
    % Set new setpoint
    fprintf('Set sensor regulation to %f\n', sensorSetpoint)
    fgt_set_sensorRegulation(0, 0, sensorSetpoint)
    % Wait 1 second
    pause(1)
    % Read sensor value
    sensorMeasurement = fgt_get_sensorValue(0);
    fprintf('Current sensor value: %f\n', sensorMeasurement);
end

%% Close the session
% Set pressure to 0 before closing (also stops regulation)
fgt_set_pressure(0, 0)
fgt_close

%%
% Copyright (c) Fluigent 2019.  All Rights Reserved.