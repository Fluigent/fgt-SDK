function [error_code] = fgt_set_log_output_mode( output_to_file, output_to_stderr, output_to_queue )
%FGT_SET_LOG_OUTPUT_MODE Summary of this function goes here
%   Detailed explanation goes here
load_fgt
[error_code] = calllib('fgt_sdk', 'fgt_set_log_output_mode', output_to_file, output_to_stderr, output_to_queue );

end

