function [PMin, PMax, error_code ] = fgt_get_pressureRange( pressureIndex )
%FGT_GET_PRESSURERANGE Get pressure controller minimum and maximum range. 
% 
% [PMin, PMax ] = fgt_get_pressureRange( pressureIndex ) returns the pressure 
% minimum and maximum value in the selected unit. Default unit is 'mbar'
%
% [PMin, PMax, error_code ] = fgt_get_pressureRange( pressureIndex ) also
% returns the error code returned by the library function

[error_code, PMin, PMax] = LowLevel.fgt_get_pressureRange(pressureIndex);
manage_pressure_status('fgt_get_pressureRange', pressureIndex);
error_code = fgt_ERROR_CODE(error_code);
end

