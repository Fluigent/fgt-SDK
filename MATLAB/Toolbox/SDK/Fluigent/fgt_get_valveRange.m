function [posMax, error_code] = fgt_get_valveRange( valveIndex )
%FGT_GET_VALVERANGE Returns the maximum position of the valve. 
% 
% [posMax] = fgt_get_valveRange( sensorIndex ) returns the maximum
% position of the valve at the specified index.
%
% [posMax, error_code] = fgt_get_valveRange( valveIndex ) also returns the
% error code returned by the library function.

[error_code, posMax] = LowLevel.fgt_get_valveRange(valveIndex);
manage_generic_status('fgt_get_valveRange', error_code);
error_code = fgt_ERROR_CODE(error_code);
end

