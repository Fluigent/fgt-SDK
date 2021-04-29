function [unit, error_code] = fgt_get_sensorUnit( sensorIndex )
%FGT_GET_SENSORUNIT Description Get current unit on selected sensor device.
% 
% unit = fgt_get_sensorUnit( sensorIndex ) returns the current sensor 
% unit as a string. Default unit is 'µl/min' for Flow Units and 'mbar' 
% for IPS modules.
%
% [unit, error_code] = fgt_get_sensorUnit( sensorIndex ) also returns the
% error code returned by the library function.

[error_code, unit] = LowLevel.fgt_get_sensorUnit(sensorIndex);
manage_sensor_status('fgt_get_sensorUnit', sensorIndex);
error_code = fgt_ERROR_CODE(error_code);
end

