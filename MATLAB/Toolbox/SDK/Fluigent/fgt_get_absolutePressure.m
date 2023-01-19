function [PAbs, error_code ] = fgt_get_absolutePressure( sensorIndex )
%FGT_GET_ABSOLUTEPRESSURE Returns the absolute pressure measurement in mbar
%
% This feature is only available on NIFS devices.
%
% PAbs = fgt_get_absolutePressure( sensorIndex ) returns the
% absolute pressure measurement in mbar.
%
% [PAbs, error_code ] = fgt_get_absolutePressure( sensorIndex ) also
% returns the error code returned by the library function

[error_code, PAbs] = LowLevel.fgt_get_absolutePressure(sensorIndex);
manage_sensor_status('fgt_get_absolutePressure', sensorIndex);
error_code = fgt_ERROR_CODE(error_code);
end

