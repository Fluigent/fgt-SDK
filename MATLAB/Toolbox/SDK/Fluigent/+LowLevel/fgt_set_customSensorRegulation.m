function [ error_code ] = fgt_set_customSensorRegulation(measure, setpoint, maxSensorRange, pressureIndex)
%FGT_SET_CUSTOMSENSORREGULATION Summary of this function goes here
%   Detailed explanation goes here
load_fgt
[error_code] = calllib('fgt_sdk', 'fgt_set_customSensorRegulation', ...
                measure, setpoint, maxSensorRange, pressureIndex);

end

