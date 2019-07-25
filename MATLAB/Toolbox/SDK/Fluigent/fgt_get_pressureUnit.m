function [unit] = fgt_get_pressureUnit( pressureIndex )
%FGT_GET_PRESSUREUNIT Get current unit on selected pressure device.
% 
% unit = fgt_get_pressureUnit( pressureIndex ) returns the current unit as
% a string. Default unit is 'mbar'

[~, unit] = LowLevel.fgt_get_pressureUnit(pressureIndex);
manage_pressure_status('fgt_get_pressureUnit', pressureIndex);
end

