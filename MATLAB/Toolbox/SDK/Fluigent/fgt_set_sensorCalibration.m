function [] = fgt_set_sensorCalibration( sensorIndex, calibration )
%FGT_SET_SENSORCALIBRATION Set used sensor internal calibration table. 
% 
% fgt_set_sensorCalibration(sensorIndex, calibration) sets the calibration
% table on the selected channel to the specified value from the
% fgt_SENSOR_CALIBRATION enum.
%
% Function is only available for specific sensors (dual type) such as
% the Flow Unit M accepting H2O and IPA.
% 
% Examples
% % Set the first sensor to isopropanol
% fgt_set_sensorCalibration(0, fgt_SENSOR_CALIBRATION.IPA)
% % Set the second sensor to water
% fgt_set_sensorCalibration(1, fgt_SENSOR_CALIBRATION.H20)

calibration = uint8(calibration);
LowLevel.fgt_set_sensorCalibration( sensorIndex, calibration );
manage_sensor_status('fgt_set_sensorCalibration', sensorIndex);
end

