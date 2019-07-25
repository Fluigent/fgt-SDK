function [ ] = fgt_set_manual( pressureIndex, value )
%FGT_SET_MANUAL Manually set internal solenoid valve voltage. 
% 
% fgt_set_manual( pressureIndex, value ) sets the voltage on the selected
% pressure channel's internal valve to the specified value (0 to 100) as a
% percentage of its maximum voltage. This stops pressure regulation on the
% channel until a new pressure or flow rate command is set.
% 
% This feature is only available on MFCS and MFCS-EZ devices.

LowLevel.fgt_set_manual(pressureIndex, value);
manage_pressure_status('fgt_set_manual', pressureIndex);
end

