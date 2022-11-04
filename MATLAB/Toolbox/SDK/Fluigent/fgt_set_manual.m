function varargout = fgt_set_manual( pressureIndex, value )
%FGT_SET_MANUAL Manually set internal solenoid valve voltage. 
% 
% fgt_set_manual( pressureIndex, value ) sets the voltage on the selected
% pressure channel's internal valve to the specified value (0 to 100) as a
% percentage of its maximum voltage. This stops pressure regulation on the
% channel until a new pressure or flow rate command is set.
%
% error_code = fgt_set_manual( pressureIndex, value ) also returns the
% error code returned by the library function.

error_code = LowLevel.fgt_set_manual(pressureIndex, value);
manage_pressure_status('fgt_set_manual', pressureIndex);
if nargout > 0
    varargout = {fgt_ERROR_CODE(error_code)};
end
end

