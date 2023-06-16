function [log_entry, error_code] = fgt_get_next_log( )
%FGT_GET_NEXT_LOG Returns the next log entry stored in memory, if any, and removes it from the queue
% 
% Logs are only stored in memory if the corresponding option is set with the
% fgt_set_log_output_mode function.
%
% Also note that logging is disabled by default. Use the fgt_set_log_verbosity
% function to enable it.
% 
% log_entry = fgt_get_next_log( ) returns the oldest log stored in the internal
% buffer, or an empty string if the queue is empty. If a log is returned, it is
% removed from the queue. a string. Default unit is 'mbar'
%
% [log_entry, error_code] = fgt_get_next_log( ) also returns
% the error code returned by the library function. The error will be non-zero
% if the log queue is empty.
%
% See also:
%     fgt_set_log_output_mode
%     fgt_set_log_verbosity

[error_code, log_entry] = LowLevel.fgt_get_next_log();
error_code = fgt_ERROR_CODE(error_code);
end

