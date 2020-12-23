%% Basic Read Sensor Data
% This example shows how to retrieve data from a sensor channel
% 			
% Requires at least one Fluigent sensor (Flow Unit or IPS)
%
% <matlab:edit('Fluigent_SDK_BasicReadSensorData') Open this M File>

%% Initialize the session
% This step is optional, if not called session will be automatically
% created
fgt_init

%% Get information about sensors and read them

[sensorInfoArray, sensorTypeArray] = fgt_get_sensorChannelsInfo;
for i=1:numel(sensorInfoArray)
    % SDK indices start at 0
    sensorIndex = i-1;
    fprintf('Sensor channel info at index: %d\n', sensorIndex);
    disp(sensorInfoArray(i));
    fprintf('Sensor type: %s\n', fgt_SENSOR_TYPE(sensorTypeArray(i)));
    % Get measurement unit
    unit = fgt_get_sensorUnit(sensorIndex);
    % Get sensor range
    [minSensor, maxSensor] = fgt_get_sensorRange(sensorIndex);
    fprintf('Range %.2f to %.2f %s\n', minSensor, maxSensor, unit);
    % Read the sensor repeatedly
    for j=1:5
        measurement = fgt_get_sensorValue(sensorIndex);
        fprintf('Measured %.2f %s\n', measurement, unit);
        pause(0.2)
    end
end

%% Close the session
fgt_close

%%
% Copyright (c) Fluigent 2020.  All Rights Reserved.