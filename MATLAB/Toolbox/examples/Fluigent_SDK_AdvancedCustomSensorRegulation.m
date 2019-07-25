%% Advanced Custom Sensor Regulation
% This example shows how to use a custom sensor, different from
% Fluigent ones and regulate pressure in order to reach the setpoint.
% Different sensor types and ranges can be used (e.g. liquid pressure,
% water level, l/min flow meter...), however, we do not guarantee 
% full compatibility with all sensors.
% For this demonstration, a Fluigent Flow Unit is used for more simplicity.
%
% Requires at least one Fluigent pressure controller (MFCS, MFCS-EZ or Flow
% EZ)
%
% <matlab:edit('Fluigent_SDK_AdvancedCustomSensorRegulation') Open this M File>

%% Initialize the session
% This step is optional, if not called session will be automatically
% created
fgt_init

%% Get sensor range
% When using a custom sensor, its range has to be known.
% Replace this function with your custom sensor interface.
[minSensor, maxSensor] = fgt_get_sensorRange(0);

%% Run regulation

% Read sensor value. Replace with your custom sensor's interface
sensorMeasurement = fgt_get_sensorValue(0);

% Loop for 10 seconds waiting 100ms between each sensor update
for i=1:100
    % Replace this function with your custom sensor's interface
    sensorMeasurement = fgt_get_sensorValue(0);
    % Update regulation with sensor values. Here setpoint is set to 50% of
    % sensor range, first pressure channel of the list is used
	fprintf('Running custom regulation, read: %f, setpoint: %f\n', sensorMeasurement, maxSensor / 2 );
    fgt_set_customSensorRegulation(sensorMeasurement, maxSensor/2 , maxSensor, 0);
    % Wait 100 milliseconds. Wait time between two successive updates
    % should be 1 seconds or less, otherwise pressure regulation is
    % stopped
    pause(0.1)
end

%% Close the session
% Set pressure to 0 before closing
fgt_set_pressure(0, 0)
fgt_close

%%
% Copyright (c) Fluigent 2019.  All Rights Reserved.