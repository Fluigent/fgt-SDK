function [ error_code ] = fgt_set_pressure( pressureIndex, pressure )
%FGT_SET_PRESSURE Summary of this function goes here
%   Detailed explanation goes here
load_fgt
[error_code] = calllib('fgt_sdk', 'fgt_set_pressure', pressureIndex, pressure);

end

