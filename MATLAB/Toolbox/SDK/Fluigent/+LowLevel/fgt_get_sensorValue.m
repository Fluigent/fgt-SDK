function [error_code, value] = fgt_get_sensorValue( sensorIndex )
%FGT_GET_SENSORVALUE Summary of this function goes here
%   Detailed explanation goes here
load_fgt
value = 0;
[error_code, value] = calllib('fgt_sdk', 'fgt_get_sensorValue', sensorIndex, value);

end

