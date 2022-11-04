function [error_code] = fgt_set_sensorBypassValve( sensorIndex, state )
%FGT_SET_SENSORBYPASSVALVE Summary of this function goes here
%   Detailed explanation goes here
load_fgt
[error_code] = calllib('fgt_sdk', 'fgt_set_sensorBypassValve', sensorIndex, state);

end

