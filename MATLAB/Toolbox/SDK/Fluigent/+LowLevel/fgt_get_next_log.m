function [error_code, log_entry] = fgt_get_next_log( )
%FGT_GET_NEXT_LOG Summary of this function goes here
%   Detailed explanation goes here
load_fgt
log_entry = zeros(1, 2000);
[error_code, log_entry] = calllib('fgt_sdk', 'fgt_get_next_log', log_entry);

end

