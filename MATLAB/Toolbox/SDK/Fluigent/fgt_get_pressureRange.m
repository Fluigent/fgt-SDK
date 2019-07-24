function [PMin, PMax ] = fgt_get_pressureRange( pressureIndex )
%FGT_GET_PRESSURERANGE Get pressure controller minimum and maximum range. 
% 
% [PMin, PMax ] = fgt_get_pressureRange( pressureIndex ) returns the pressure 
% minimum and maximum value in the selected unit. Default unit is 'mbar'

[~, PMin, PMax] = LowLevel.fgt_get_pressureRange(pressureIndex);
manage_pressure_status('fgt_get_pressureRange', pressureIndex);
end

