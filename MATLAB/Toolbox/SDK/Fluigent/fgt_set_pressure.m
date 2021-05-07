function varargout = fgt_set_pressure( pressureIndex, pressure )
%FGT_SET_PRESSURE Send pressure command to selected device.
% 
% fgt_set_pressure(pressureIndex, pressure) sets the pressure on the
% selected channel to the specified value, in the channel's current unit.
% Default unit is 'mbar'
%
% error_code = fgt_set_pressure(pressureIndex, pressure) also returns the
% error code returned by the library function.
%
% See also:
%     fgt_set_sensorRegulation

error_code = LowLevel.fgt_set_pressure(pressureIndex, pressure);
manage_pressure_status('fgt_set_pressure', pressureIndex);
if nargout > 0
    varargout = {fgt_ERROR_CODE(error_code)};
end
end

