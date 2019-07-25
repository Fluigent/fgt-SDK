function [error_code, calibration] = fgt_get_sensorCalibration( sensorIndex )
%FGT_GET_SENSORCALIBRATION Summary of this function goes here
%   Detailed explanation goes here
load_fgt
calibration = uint8(0);
[error_code, calibration] = calllib('fgt_sdk', 'fgt_get_sensorCalibration', sensorIndex, calibration);

end

