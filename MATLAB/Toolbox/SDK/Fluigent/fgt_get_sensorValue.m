function varargout = fgt_get_sensorValue( sensorIndex )
%FGT_GET_SENSORVALUE Read sensor value of selected device
%
% sensorValue = fgt_get_sensorValue( sensorIndex ) returns the sensor 
% measurement in the selected unit. Default is 'µl/min' for flowrate 
% sensors and 'mbar' for IPS modules.
%
% [sensorValue, timestamp] = fgt_get_sensorValue( sensorIndex ) returns the
% instrument's internal timestamp in addition to the sensor value. The IPS
% does not support this feature and always returns a timestamp of zero.

[~, value, timestamp] = LowLevel.fgt_get_sensorValueEx(sensorIndex);
manage_sensor_status('fgt_get_sensorValue', sensorIndex);
varargout = {value, timestamp};
end

