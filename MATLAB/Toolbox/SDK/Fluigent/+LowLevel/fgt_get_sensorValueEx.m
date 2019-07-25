function [error_code, value, timestamp] = fgt_get_sensorValueEx( sensorIndex )
%FGT_GET_SENSORVALUEEX Summary of this function goes here
%   Detailed explanation goes here
load_fgt
value = 0;
timestamp = uint16(0);
[error_code, value, timestamp] = calllib('fgt_sdk', 'fgt_get_sensorValueEx', sensorIndex, value, timestamp);

end

