function [SMin, SMax, error_code] = fgt_get_sensorRange( sensorIndex )
%FGT_GET_SENSORRANGE Description Get sensor minimum and maximum range. 
% 
% [SMin, SMax] = fgt_get_sensorRange( sensorIndex ) returns the sensor 
% minimum and maximum value in the selected unit. Default unit is
% 'µl/min' for Flow Units and 'mbar' for IPS modules.
%
% [SMin, SMax, error_code] = fgt_get_sensorRange( sensorIndex ) also
% returns the error code returned by the library function.

[error_code, SMin, SMax] = LowLevel.fgt_get_sensorRange(sensorIndex);
manage_sensor_status('fgt_get_sensorRange', sensorIndex);
error_code = fgt_ERROR_CODE(error_code);
end

