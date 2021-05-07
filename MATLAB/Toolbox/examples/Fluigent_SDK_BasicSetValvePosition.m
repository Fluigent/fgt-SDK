%% Basic Set Valve Position
% 
% This example shows how to change the position of a valve
% 
% Requires at least one Fluigent valve controller (M-Switch, L-Switch,
% 2-Switch or P-Switch)
%
% <matlab:edit('Fluigent_SDK_BasicSetValvePosition') Open this M File>

%% Initialize the session
% This step is optional, if not called session will be automatically
% created
fgt_init

%% Set each valve to all of its available positions

% Get number of valves
nValves = fgt_get_valveChannelCount;

for valveIndex = 0:nValves-1
    fprintf('valve %d is at position %d\n', valveIndex, fgt_get_valvePosition(valveIndex))
    % Get all available positions for this valve
    maxPosition = fgt_get_valveRange(valveIndex);
    % Set valve to each of the available positions, waiting for it to switch each time
    for position=0:maxPosition
        fgt_set_valvePosition(valveIndex, position);
        fprintf('valve %d is at position %d\n', valveIndex, fgt_get_valvePosition(valveIndex))
    end
    % Return valve to default position
    fgt_set_valvePosition(valveIndex, 0);
end

%% Close the session
fgt_close

%%
% Copyright (c) Fluigent 2021.  All Rights Reserved.