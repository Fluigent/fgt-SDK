function varargout = fgt_set_digitalOutput( controllerIndex, port, state )
%FGT_SET_DIGITALOUTPUT Turns the digital output on or off
% 
% fgt_set_digitalOutput(controllerIndex, port, state) turns the digital
% output ON if state is 1 and OFF if state is 0.
%
% error_code = fgt_set_digitalOutput(controllerIndex, port, state) also
% returns the error code returned by the library function.
%
% This feature is only available on F-OEM devices.
% On the F-OEM, port 0 corresponds to the pump output, and port 1
% corresponds to the LED

error_code = LowLevel.fgt_set_digitalOutput( controllerIndex, port, state );
manage_generic_status('fgt_set_digitalOutput', error_code);
if nargout > 0
    varargout = {fgt_ERROR_CODE(error_code)};
end
end

