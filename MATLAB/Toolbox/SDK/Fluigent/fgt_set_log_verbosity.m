function varargout = fgt_set_log_verbosity( verbosity )
%FGT_SET_LOG_VERBOSITY Sets the verbosity of the logging feature, i.e., how much data is logged
% 
% fgt_set_log_verbosity(0) Disables logging. This is the default setting.
%
% fgt_set_log_verbosity(1) Enables logging only for errors.
%
% fgt_set_log_verbosity(2) Enables logging for errors and warnings.
%
% fgt_set_log_verbosity(5) Enables all logs.
%
% error_code = fgt_set_log_verbosity(verbosity) also returns the error code
% returned by the library function.
%
% See also:
%     fgt_set_log_output_mode
%     fgt_get_next_log

error_code = LowLevel.fgt_set_log_verbosity( verbosity );
manage_generic_status('fgt_set_log_verbosity', error_code);
if nargout > 0
    varargout = {fgt_ERROR_CODE(error_code)};
end
end

