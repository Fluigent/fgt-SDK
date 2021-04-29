function varargout = fgt_set_pressureLimit( pressureIndex, PlimMin, PlimMax )
%FGT_SET_PRESSURELIMIT Set pressure hard limits. 
% 
% fgt_set_pressureLimit(pressureIndex, PlimMin, PlimMax) sets the minimum and
% maximum pressure on the selected channel to the specified values, in the
% channel's current unit. Default unit is 'mbar'
%
% error_code = fgt_set_pressureLimit(pressureIndex, PlimMin, PlimMax) also
% returns the error code returned by the library function.
% 
% Pressure setpoint will not exceed these limit during regulation.
% This function is useful to protect your microfluidic system.

error_code = LowLevel.fgt_set_pressureLimit( pressureIndex, PlimMin, PlimMax );
manage_pressure_status('fgt_set_pressureLimit', pressureIndex);
if nargout > 0
    varargout = {fgt_ERROR_CODE(error_code)};
end
end

