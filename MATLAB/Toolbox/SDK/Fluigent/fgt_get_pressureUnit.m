function [unit, error_code] = fgt_get_pressureUnit( pressureIndex )
%FGT_GET_PRESSUREUNIT Get current unit on selected pressure device.
% 
% unit = fgt_get_pressureUnit( pressureIndex ) returns the current unit as
% a string. Default unit is 'mbar'
%
% [unit, error_code] = fgt_get_pressureUnit( pressureIndex ) also returns
% the error code returned by the library function

[error_code, unit] = LowLevel.fgt_get_pressureUnit(pressureIndex);
manage_pressure_status('fgt_get_pressureUnit', pressureIndex);
error_code = fgt_ERROR_CODE(error_code);
end

