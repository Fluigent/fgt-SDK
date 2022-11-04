function [PMin, PMax, error_code ] = fgt_get_absolutePressureRange( sensorIndex )
%FGT_GET_ABSOLUTEPRESSURERANGE Returns the range of the absolute pressure sensor in mbar
%
% This feature is only available on NIFS devices.
%
% [PMin, PMax ] = fgt_get_absolutePressureRange( sensorIndex ) returns the minimum and maximum
% values for the absolute pressure in mbar.
%
% [PMin, PMax, error_code ] = fgt_get_absolutePressureRange( sensorIndex ) also
% returns the error code returned by the library function

[error_code, PMin, PMax] = LowLevel.fgt_get_absolutePressureRange(sensorIndex);
manage_sensor_status('fgt_get_absolutePressureRange', sensorIndex);
error_code = fgt_ERROR_CODE(error_code);
end

