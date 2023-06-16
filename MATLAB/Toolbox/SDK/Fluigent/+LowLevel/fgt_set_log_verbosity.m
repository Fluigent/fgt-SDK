function [error_code] = fgt_set_log_verbosity( verbosity )
%FGT_SET_LOG_VERBOSITY Summary of this function goes here
%   Detailed explanation goes here
load_fgt
[error_code] = calllib('fgt_sdk', 'fgt_set_log_verbosity', verbosity);

end

