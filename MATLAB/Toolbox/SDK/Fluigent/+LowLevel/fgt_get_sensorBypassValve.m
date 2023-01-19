function [error_code, state] = fgt_get_sensorBypassValve( sensorIndex )
%FGT_GET_SENSORBYPASSVALVE Summary of this function goes here
%   Detailed explanation goes here
load_fgt
state = uint8(0);
[error_code, state] = calllib('fgt_sdk', 'fgt_get_sensorBypassValve', sensorIndex, state);

end

