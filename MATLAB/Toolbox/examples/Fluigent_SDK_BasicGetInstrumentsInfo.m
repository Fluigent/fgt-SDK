%% Basic Get Instruments Info
% This example shows how to retrieve information about Fluigent 
% instruments: type, controller, serial number, unique ID...
% 			
% Requires at least one Fluigent pressure or sensor module
%
% <matlab:edit('Fluigent_SDK_BasicGetInstrumentsInfo') Open this M File>

%% Get serial numbers and types of detected Fluigent controllers

% Detect all controllers
[SNs, types] = fgt_detect;
controllerCount = numel(SNs);
fprintf('Number of controllers detected: %d\n', controllerCount);

% List all found controllers' serial number and type
for i=1:numel(SNs)
    fprintf('Detected instrument at index: %d, ControllerSN: %d, type: %s\n',...
        i-1, SNs(i), char(types(i)));
end
fprintf('\n');

%% Initialize specific instruments
%  Initialize only specific instrument controllers here If you do not want
%  a controller in the list or if you want a specific order (e.g. LineUP
%  before MFCS instruments), rearrange parsed SN table
fgt_init(SNs)

%% Get the number of channels of each type

% Get total number of initialized pressure channels
fprintf('Total number of pressure channels: %d\n', fgt_get_pressureChannelCount);

% Get total number of initialized pressure channels
fprintf('Total number of sensor channels: %d\n', fgt_get_sensorChannelCount);

% Get total number of initialized TTL channels
fprintf('Total number of TTL channels: %d\n', fgt_get_TtlChannelCount);

% Get total number of initialized valve channels
fprintf('Total number of valve channels: %d\n\n', fgt_get_valveChannelCount);
    
%% Helper functions to format the instrument data

printVersion = @(ver) sprintf('%x.%02x',floor(ver/256),mod(ver,256));

printController = @(controller) sprintf(...
    ['SN: %d\n'...
     'Firmware: %s\n'...
     'Unique ID: %d\n'...
     'Instrument series: %s\n'...
     ], controller.SN, printVersion(controller.Firmware),...
     controller.id, controller.InstrType);
 
printChannel = @(channel) sprintf(...
    ['Controller SN: %d\n'...
     'Firmware: %s\n'...
     'Device SN: %d\n'...
     'Position: %d\n'...
     'Unique ID: %d\n'...
     'Instrument series: %s\n'...
     ], channel.ControllerSN, printVersion(channel.firmware), channel.DeviceSN,...
     channel.position, channel.indexID, channel.InstrType);
 
%% Get detailed information about all controllers
controllerInfoArray = fgt_get_controllersInfo;
for i=1:numel(controllerInfoArray)
    fprintf('Controller at index %d:\n', i-1);
    fprintf('%s\n', printController(controllerInfoArray(i)));
end

%% Get detailed information about all pressure channels

pressureInfoArray = fgt_get_pressureChannelsInfo;
for i=1:numel(pressureInfoArray)
    fprintf('Pressure channel at index %d:\n', i-1);
    fprintf('%s\n', printChannel(pressureInfoArray(i)));
end

%% Get detailed information about all sensor channels

[sensorInfoArray, sensorTypeArray] = fgt_get_sensorChannelsInfo;
for i=1:numel(sensorInfoArray)
    fprintf('Sensor channel at index %d (%s):\n', i-1, char(fgt_SENSOR_TYPE(sensorTypeArray(i))));
    fprintf('%s\n', printChannel(sensorInfoArray(i)));
end

%% Get detailed information about all TTL channels

ttlInfoArray = fgt_get_TtlChannelsInfo;
for i=1:numel(ttlInfoArray)
    fprintf('TTL channel at index: %d:\n', i-1);
    fprintf('%s\n', printChannel(ttlInfoArray(i)));
end

%% Get detailed information about all sensor channels

[valveInfoArray, valveTypeArray] = fgt_get_valveChannelsInfo;
for i=1:numel(valveInfoArray)
    fprintf('Valve channel info at index %d (%s):\n', i-1, char(fgt_VALVE_TYPE(valveTypeArray(i))));
    fprintf('%s\n', printChannel(valveInfoArray(i)));
end

%% Close the session
fgt_close

%%
% Copyright (c) Fluigent 2021.  All Rights Reserved.
