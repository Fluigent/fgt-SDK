function [ error_code ] = fgt_set_sensorCustomScale(sensorIndex, a, b, c)
%FGT_SET_SENSORCUSTOMSCALE Summary of this function goes here
%   Detailed explanation goes here
load_fgt
[error_code] = calllib('fgt_sdk', 'fgt_set_sensorCustomScale', sensorIndex, a, b, c);

end

