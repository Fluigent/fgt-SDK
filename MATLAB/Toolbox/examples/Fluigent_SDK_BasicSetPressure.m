%% Basic Set Pressure
% This example shows how to set a pressure order and generate a ramp on the
% first pressure module of the chain
% 			
% Requires at least one Fluigent pressure controller (MFCS, MFCS-EZ or Flow
% EZ)
%
% <matlab:edit('Fluigent_SDK_BasicSetPressure') Open this M File>

%% Initialize the session
% This step is optional, if not called session will be automatically
% created
fgt_init

%% Set and read pressure

% Set pressure to 20 mbar on first pressure channel of the list
% mbar is the default unit at initialization
fgt_set_pressure(0, 20);

% Wait 5 seconds for the pressure to settle
disp('Waiting 5 seconds...');
pause(5)

% Read pressure value
pressureMeasurement = fgt_get_pressure(0);
fprintf('Current pressure: %f\n', pressureMeasurement)

%% Create a pressure ramp profile 
% The ramp goes from device minimal to maximal pressure in 10 steps

% Create the pressure steps
[pMin, pMax] = fgt_get_pressureRange(0);
stepSize = (pMax-pMin)/10;
pressureSteps = pMin:stepSize:pMax;

for pressureSetpoint = pressureSteps
    % Set pressure
    fprintf('Set pressure to %f\n', pressureSetpoint)
    fgt_set_pressure(0, pressureSetpoint)
    % Wait 1 second
    pause(1)
    % Read pressure
    pressureMeasurement = fgt_get_pressure(0);
    fprintf('Current pressure: %f\n', pressureMeasurement)
end

%% Close the session
% Set pressure to 0 before closing
fgt_set_pressure(0, 0)
fgt_close

%%
% Copyright (c) Fluigent 2019.  All Rights Reserved.