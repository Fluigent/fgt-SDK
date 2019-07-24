function [ error_code ] = fgt_set_sensorCustomScaleEx(sensorIndex, a, b, c, SMax)
%FGT_SET_SENSORCUSTOMSCALEEX Summary of this function goes here
%   Detailed explanation goes here
load_fgt
[error_code] = calllib('fgt_sdk', 'fgt_set_sensorCustomScaleEx', sensorIndex, a, b, c, SMax);

end

