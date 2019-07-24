%% Advanced Specific Multiple Instruments
% This example shows how to use specific channels ID and multiple connected
% instruments
%
% <matlab:edit('Fluigent_SDK_AdvancedSpecificMultipleInstruments') Open this M File>

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

%% Initialize specific instruments
%  Initialize only specific instrument controllers here If you do not want
%  a controller in the list or if you want a specific order (e.g. LineUP
%  before MFCS instruments), rearrange parsed SN table
fgt_init(SNs)

%% Get the number of pressure channels

% Get total number of initialized pressure channels
fprintf('Total number of pressure channels: %d\n', fgt_get_pressureChannelCount);
    
%% Get detailed information about all controllers

controllerInfoArray = fgt_get_controllersInfo;
for i=1:numel(controllerInfoArray)
    fprintf('Controller info at index: %d\n', i-1);
    disp(controllerInfoArray(i));
end

%% Get detailed information about all pressure channels

pressureInfoArray = fgt_get_pressureChannelsInfo;
for i=1:numel(pressureInfoArray)
    fprintf('Pressure channel info at index: %d\n', i-1);
    disp(pressureInfoArray(i));
end

%% Read pressure using unique ID
% If you want to address a specific channel, unique ID can be used. However
% if hardware changed channel may not be found

pressure1 = fgt_get_pressure(pressureInfoArray(1).indexID);
fprintf('Read pressure from ID %d : %f\n', pressureInfoArray(1).indexID,  pressure1);
pressure2 = fgt_get_pressure(pressureInfoArray(2).indexID);
fprintf('Read pressure from ID %d : %f\n', pressureInfoArray(2).indexID,  pressure2);

%% Close the session
fgt_close

%%
% Copyright (c) Fluigent 2019.  All Rights Reserved.