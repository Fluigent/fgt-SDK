function [] = fgt_set_sensorCalibration( sensorIndex, calibration )
%FGT_SET_SENSORCALIBRATION Set sensor calibration table or zero value. 
% 
% fgt_set_sensorCalibration(sensorIndex, calibration) sets the calibration
% table on the selected channel to the specified value from the
% fgt_SENSOR_CALIBRATION enum, if the sensor is a Flow Unit.
% Function is only available for specific sensors (dual type) such as
% the Flow Unit M accepting H2O and IPA.
%
% For IPS modules, calling this function sets the current pressure 
% measurement as the sensor's zero value. The calibration argument is
% ignored in this case.
% 
% Examples
% % Set the first sensor to isopropanol
% fgt_set_sensorCalibration(0, fgt_SENSOR_CALIBRATION.IPA)
% % Set the second sensor to water
% fgt_set_sensorCalibration(1, fgt_SENSOR_CALIBRATION.H20)
% % Set zero value on the third sensor (if it is an IPS)
% fgt_set_sensorCalibration(2, fgt_SENSOR_CALIBRATION.None)

calibration = uint8(calibration);
LowLevel.fgt_set_sensorCalibration( sensorIndex, calibration );
manage_sensor_status('fgt_set_sensorCalibration', sensorIndex);
end

