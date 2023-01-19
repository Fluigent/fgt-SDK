function [PDiff, error_code ] = fgt_get_differentialPressure( sensorIndex )
%FGT_GET_DIFFERENTIALPRESSURE Returns the differential pressure measurement in mbar
%
% This feature is only available on NIFS devices.
%
% PDiff = fgt_get_differentialPressure( sensorIndex ) returns the
% differential pressure measurement in mbar.
%
% [PDiff, error_code ] = fgt_get_differentialPressure( sensorIndex ) also
% returns the error code returned by the library function

[error_code, PDiff] = LowLevel.fgt_get_differentialPressure(sensorIndex);
manage_sensor_status('fgt_get_differentialPressure', sensorIndex);
error_code = fgt_ERROR_CODE(error_code);
end

