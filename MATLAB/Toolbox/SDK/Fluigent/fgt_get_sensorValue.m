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
%
% [sensorValue, timestamp, error_code] = fgt_get_sensorValue( sensorIndex )
% also returns the error code returned by the library function.

[error_code, value, timestamp] = LowLevel.fgt_get_sensorValueEx(sensorIndex);
manage_sensor_status('fgt_get_sensorValue', sensorIndex);
error_code = fgt_ERROR_CODE(error_code);
varargout = {value, timestamp, error_code};
end

