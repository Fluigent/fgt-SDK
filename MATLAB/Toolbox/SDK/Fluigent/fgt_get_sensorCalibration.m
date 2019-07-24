function [calibration] = fgt_get_sensorCalibration( sensorIndex )
%FGT_GET_SENSORCALIBRATION Get sensor's current calibration table.
% 
% calibration = fgt_get_sensorCalibration( sensorIndex ) returns the sensor's 
% current calibration table as a value from the fgt_SENSOR_CALIBRATION enum

[~, calibration] = LowLevel.fgt_get_sensorCalibration(sensorIndex);
calibration = fgt_SENSOR_CALIBRATION(calibration);
manage_sensor_status('fgt_get_sensorCalibration', sensorIndex);
end

