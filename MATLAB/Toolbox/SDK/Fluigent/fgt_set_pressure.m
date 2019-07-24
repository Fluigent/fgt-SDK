function [] = fgt_set_pressure( pressureIndex, pressure )
%FGT_SET_PRESSURE Send pressure command to selected device.
% 
% fgt_set_pressure(pressureIndex, pressure) sets the pressure on the
% selected channel to the specified value, in the channel's current unit.
% Default unit is 'mbar'
%
% See also:
%     fgt_set_sensorRegulation

LowLevel.fgt_set_pressure(pressureIndex, pressure);
manage_pressure_status('fgt_set_pressure', pressureIndex);
end

