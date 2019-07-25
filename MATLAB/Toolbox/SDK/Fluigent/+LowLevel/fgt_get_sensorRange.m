function [error_code, SMin, SMax] = fgt_get_sensorRange( sensorIndex )
%FGT_GET_SENSORRANGE Summary of this function goes here
%   Detailed explanation goes here
load_fgt
SMin = 0;
SMax = 0;
[error_code, SMin, SMax] = calllib('fgt_sdk', 'fgt_get_sensorRange', sensorIndex, SMin, SMax);

end

