function [] = fgt_set_pressureUnit( pressureIndex, unit )
%FGT_SET_PRESSUREUNIT Set pressure unit on selected pressure device.
% 
% fgt_set_pressureUnit(pressureIndex, unit) sets the unit to be used on the
% selected pressure channel, which should be passed as a string.
% 
% Default value is 'mbar'. 
%
% If the unit is invalid, the previous unit is kept and an error is logged.
% Every pressure read value and sent command will then use this unit.
%
% Examples: 
%     fgt_set_pressureUnit(0, 'mbar')
%     fgt_set_pressureUnit(1, 'psi')
% See also:
%     fgt_set_sensorUnit

LowLevel.fgt_set_pressureUnit( pressureIndex, unit );
manage_pressure_status('fgt_set_pressureUnit', pressureIndex);
end

