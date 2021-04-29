function [position, error_code] = fgt_get_valvePosition( valveIndex )
%FGT_GET_VALVEPOSITION Read the position of a specific valve channel.
%
% position = fgt_get_valvePosition( valveIndex ) returns the current 
% position of the valve.
%
% [position, error_code] = fgt_get_valvePosition( valveIndex ) also returns
% the error code returned by the library function.

[error_code, position] = LowLevel.fgt_get_valvePosition(valveIndex);
manage_generic_status('fgt_get_valvePosition', error_code);
error_code = fgt_ERROR_CODE(error_code);
end

