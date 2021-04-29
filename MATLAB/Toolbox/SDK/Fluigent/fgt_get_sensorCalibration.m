function [calibration, error_code] = fgt_get_sensorCalibration( sensorIndex )
%FGT_GET_SENSORCALIBRATION Get sensor's current calibration table.
% 
% calibration = fgt_get_sensorCalibration( sensorIndex ) returns the sensor's 
% current calibration table as a value from the fgt_SENSOR_CALIBRATION enum
%
% [calibration, error_code] = fgt_get_sensorCalibration( sensorIndex ) also
% returns the error code returned by the library function

[error_code, calibration] = LowLevel.fgt_get_sensorCalibration(sensorIndex);
calibration = fgt_SENSOR_CALIBRATION(calibration);
manage_sensor_status('fgt_get_sensorCalibration', sensorIndex);
error_code = fgt_ERROR_CODE(error_code);
end

