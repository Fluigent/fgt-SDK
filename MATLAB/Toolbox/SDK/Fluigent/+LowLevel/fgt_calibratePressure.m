function [ error_code ] = fgt_calibratePressure( pressureIndex )
%FGT_CALIBRATEPRESSURE Summary of this function goes here
%   Detailed explanation goes here
load_fgt
[error_code] = calllib('fgt_sdk', 'fgt_calibratePressure', pressureIndex);

end

