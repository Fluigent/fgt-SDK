function [] = manage_generic_status( function_name, error_code )
%MANAGE_GENERIC_STATUS Handle errors not related to a specific channel
% manage_generic_status( function_name, error_code ) produces an error
% message including the function name and which explains the error code
% returned by the low level function.
%
% This function is called automatically when a function from the toolbox
% unrelated to a specific sensor or pressure channel is called. By default,
% it sends a warning message if a non-zero error code was received.
%
% Modify this function if you want all or some of the error codes to
% generate errors (which will stop execution of the program if not
% handled).

global fgt_error_report_mode;
if strcmpi(fgt_error_report_mode, 'none')
    return;
end

error_messages = {'No error',...       
'USB communication error',...      
'Wrong command was sent',...      
'There is no module initialized at selected index',...      
'Wrong module was selected, unavailable feature',...      
'Module is in sleep mode, orders are not taken into account',...      
'Controller error',...      
'Some instruments failed to initialize',...      
'Function parameter is not correct or out of the bounds',...    
'Pressure module is in overpressure protection',...      
'Pressure module is in underpressure protection',...      
'No Fluigent instrument was found',...      
'No Fluigent pressure or sensor module was found',...      
'No Fluigent pressure controller was found',...		
'Pressure or sensor module is calibrating, read value may be incorrect',...   
'Some dependencies are not found'};

if error_code > 0
    if(error_code < numel(error_messages))
        message = error_messages{error_code+1};
    else
        message = 'Unknown error';
    end
    message = [function_name, ' error ',num2str(error_code), ': ' message];
    backtraceState = warning('query', 'backtrace');
    warning('off', 'backtrace')
    warning(message);
    warning(backtraceState);
end
end

