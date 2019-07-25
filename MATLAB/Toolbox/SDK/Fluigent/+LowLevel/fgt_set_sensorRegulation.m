function [ error_code ] = fgt_set_sensorRegulation( sensorIndex, pressureIndex, setpoint )
%FGT_SET_SENSORREGULATION Summary of this function goes here
%   Detailed explanation goes here
load_fgt
[error_code] = calllib('fgt_sdk', 'fgt_set_sensorRegulation', sensorIndex, pressureIndex, setpoint);

end

