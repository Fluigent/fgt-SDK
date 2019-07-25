function [ error_code ] = fgt_set_manual( pressureIndex, value )
%FGT_SET_MANUAL Summary of this function goes here
%   Detailed explanation goes here
load_fgt
[error_code] = calllib('fgt_sdk', 'fgt_set_manual', pressureIndex, value);

end

