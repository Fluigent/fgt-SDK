function [] = fgt_set_sensorUnit( sensorIndex, unit )
%FGT_SET_SENSORUNIT Set sensor unit on selected sensor device.
%
% fgt_set_sensorUnit(sensorIndex, unit) sets the unit to be used on the
% selected sensor, which should be passed as a string.
%
% Default value is 'µl/min' for Flow Units. 
% If the unit is invalid, the previous unit is kept and an error is logged.
% Every sensor read value and regulation command will then use this unit.
%
% Not supported by the IPS.
%
% Examples: 
%     fgt_set_sensorUnit(0, 'µl/h')
%     fgt_set_sensorUnit(1, 'ulperDay')
%     fgt_set_sensorUnit(1, 'microliter/hour')

LowLevel.fgt_set_sensorUnit(sensorIndex, unit);
manage_sensor_status('fgt_set_sensorUnit', sensorIndex);
end

