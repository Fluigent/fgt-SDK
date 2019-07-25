function [] = fgt_set_power(controllerIndex, powerState)
%FGT_SET_POWER Set power ON or OFF on a controller.
% 
% fgt_set_power(controllerIndex, powerState) will set the powered state of
% the selected controller to the specified value from the fgt_POWER
% enumeration.
%
% Not all controllers support this functionality.
%
% Examples:
% fgt_set_power(0, fgt_POWER.POWER_ON) % Power the first controller ON
% fgt_set_power(1, fgt_POWER.POWER_OFF) % Power the second controller OFF


powerState = uint8(powerState);
[error_code] = LowLevel.fgt_set_power(controllerIndex, powerState);
manage_generic_status('fgt_set_power', error_code);
end

