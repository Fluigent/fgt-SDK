function varargout = fgt_set_errorReportMode( mode )
%FGT_SET_ERRORREPORTMODE Change the position of the selected valve
% 
% fgt_set_errorReportMode( 'print' ) causes error messages to be displayed
% as warnings in the command window. This is the default setting.
%
% fgt_set_errorReportMode( 'none' ) causes error messages to be suppressed.
% Only the error code is returned by the function.

global fgt_error_report_mode;

options = {'none','print'};
if ~any(strcmpi(options, mode))
    message = ['Invalid error report mode ', mode, '. Valid modes are [', strjoin(options, ', '), ']'];
    error(message)
end
fgt_error_report_mode = mode;
end

