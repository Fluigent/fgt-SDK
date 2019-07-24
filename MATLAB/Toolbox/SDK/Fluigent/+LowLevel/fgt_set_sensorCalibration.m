function [error_code] = fgt_set_sensorCalibration( sensorIndex, calibration )
%FGT_SET_SENSORCALIBRATION Summary of this function goes here
%   Detailed explanation goes here
load_fgt
[error_code] = calllib('fgt_sdk', 'fgt_set_sensorCalibration', sensorIndex, calibration);

end

