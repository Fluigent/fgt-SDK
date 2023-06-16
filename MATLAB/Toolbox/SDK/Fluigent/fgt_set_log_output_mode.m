function varargout = fgt_set_log_output_mode( output_to_file, output_to_stderr, output_to_queue )
%FGT_SET_LOG_OUTPUT_MODE Sets how the SDK outputs the log entries
% 
% fgt_set_log_output_mode(1, 0, 0) Outputs the logs to a .log file in the
% current directory. This is the default.
%
% fgt_set_log_output_mode(0, 1, 0) Outputs the logs to the stderr pipe.
%
% fgt_set_log_output_mode(0, 0, 1) Saves the logs in an internal buffer, to be
% retrieved via the fgt_get_next_log function.
% 
% fgt_set_log_output_mode(1, 1, 0) Outputs the logs both to the file and to the
% stderr pipe. Any combination of output options is valid.
%
% error_code = fgt_set_log_output_mode(f, e, q) also returns the error code
% returned by the library function.
%
% See also:
%     fgt_set_log_verbosity
%     fgt_get_next_log

error_code = LowLevel.fgt_set_log_output_mode( output_to_file, output_to_stderr, output_to_queue );
manage_generic_status('fgt_set_log_output_mode', error_code);
if nargout > 0
    varargout = {fgt_ERROR_CODE(error_code)};
end
end

