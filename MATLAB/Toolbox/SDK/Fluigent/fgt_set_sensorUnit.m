function varargout = fgt_set_sensorUnit( sensorIndex, unit )
%FGT_SET_SENSORUNIT Set sensor unit on selected sensor device.
%
% fgt_set_sensorUnit(sensorIndex, unit) sets the unit to be used on the
% selected sensor, which should be passed as a string.
%
% error_code = fgt_set_sensorUnit(sensorIndex, unit) also returns the error
% code returned by the library function.
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

error_code = LowLevel.fgt_set_sensorUnit(sensorIndex, unit);
manage_sensor_status('fgt_set_sensorUnit', sensorIndex);
if nargout > 0
    varargout = {fgt_ERROR_CODE(error_code)};
end
end

