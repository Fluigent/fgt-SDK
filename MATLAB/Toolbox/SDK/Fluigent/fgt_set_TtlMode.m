function varargout = fgt_set_TtlMode( TtlIndex, mode )
%FGT_SET_TTLMODE Configure a specific TTL port.
% 
% fgt_set_TtlMode(TtlIndex, mode) sets the selected TTL port to the
% specified mode, as a value in the fgt_TTL_MODE enum.
%
% error_code = fgt_set_TtlMode(TtlIndex, mode) also returns the error code
% returned by the library function.
%
% Each port can be configured as as input or output, rising or falling
% edge.
% 
% Examples:
% % Set the first TTL channel as input and detect a falling edge signal
% fgt_set_TtlMode(0, fgt_TTL_MODE.DETECT_FALLING_EDGE)
% % Set the second TTL channel to output a high pulse when triggered
% fgt_set_TtlMode(1, fgt_TTL_MODE.OUTPUT_PULSE_HIGH)
% 
% See also:
%     fgt_read_Ttl
%     fgt_trigger_Ttl

mode = uint8(mode);
error_code = LowLevel.fgt_set_TtlMode( TtlIndex, mode );
manage_generic_status('fgt_set_TtlMode', error_code);
if nargout > 0
    varargout = {fgt_ERROR_CODE(error_code)};
end
end

