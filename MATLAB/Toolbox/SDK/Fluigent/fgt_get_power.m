function [powerState, error_code] = fgt_get_power(controllerIndex)
%FGT_GET_POWER Get power information about a controller.
% 
% powerState = fgt_get_power(controllerIndex) returns the powered state of
% the controller identified by controllerIndex as an fgt_POWER object.
%
% [powerState, error_code] = fgt_get_power(controllerIndex) also returns
% the error code returned by the library function
%
% Not all controllers support this functionality.

[error_code, powerState] = LowLevel.fgt_get_power(controllerIndex);
powerState = fgt_POWER(powerState);
manage_generic_status('fgt_get_power', error_code);
error_code = fgt_ERROR_CODE(error_code);
end

