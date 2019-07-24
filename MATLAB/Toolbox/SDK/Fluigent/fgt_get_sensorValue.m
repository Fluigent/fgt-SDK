function varargout = fgt_get_sensorValue( sensorIndex )
%FGT_GET_SENSORVALUE Read sensor value of selected device
%
% sensorValue = fgt_get_sensorValue( sensorIndex ) returns the sensor 
% measurement in the selected unit. Default is 'µl/min' for flowrate sensors
%
% [sensorValue, timestamp] = fgt_get_sensorValue( sensorIndex ) returns the
% instrument's internal timestamp in addition to the sensor value.

[~, value, timestamp] = LowLevel.fgt_get_sensorValueEx(sensorIndex);
manage_sensor_status('fgt_get_sensorValue', sensorIndex);
varargout = {value, timestamp};
end

