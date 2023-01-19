function [PMin, PMax, error_code ] = fgt_get_differentialPressureRange( sensorIndex )
%FGT_GET_DIFFERENTIALPRESSURERANGE Returns the range of the differential pressure sensor in mbar
%
% This feature is only available on NIFS devices.
%
% [PMin, PMax ] = fgt_get_differentialPressureRange( sensorIndex ) returns the minimum and maximum
% values for the differential pressure in mbar.
%
% [PMin, PMax, error_code ] = fgt_get_differentialPressureRange( sensorIndex ) also
% returns the error code returned by the library function

[error_code, PMin, PMax] = LowLevel.fgt_get_differentialPressureRange(sensorIndex);
manage_sensor_status('fgt_get_differentialPressureRange', sensorIndex);
error_code = fgt_ERROR_CODE(error_code);
end

