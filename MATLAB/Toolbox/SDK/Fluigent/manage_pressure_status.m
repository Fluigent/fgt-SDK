function [] = manage_pressure_status( function_name, pressure_index )
%MANAGE_PRESSURE_STATUS Handle pressure channel errors
% manage_pressure_status(function_name, pressure_index) produces an error
% message including the function name and which explains the error code
% returned by the low level function.
%
% This function is called automatically when a function from the toolbox
% related to a specific pressure channel is called. By default, it sends a
% warning message if a non-zero error code is returned by the pressure
% status function.
%
% Modify this function if you want all or some of the error codes to
% generate errors (which will stop execution of the program if not
% handled).

instr_types = {'None', 'MFCS', 'MFCS-EZ', 'FRP', 'LineUP', 'IPS'};

[error_code, type, instrSN, infoCode, detail] = LowLevel.fgt_get_pressureStatus(pressure_index);

if error_code == 0
    return
end

if type < 0 || type > numel(instr_types)-1
    type = 0;
end

info = '';
if infoCode == 0
    info = 'info: remote control';
elseif infoCode == 1
    info = 'info: local control';
end

message = [function_name, ' pressure channel ', num2str(pressure_index),...
           ' of type ', instr_types{type+1}, ' error ', num2str(error_code),...
           ': ', detail, '.'];
if type > 0
    message = [message, ' Controller SN: ',  num2str(instrSN), ' ', info];
end
backtraceState = warning('query', 'backtrace');
warning('off', 'backtrace')
warning(message);
warning(backtraceState);
end

