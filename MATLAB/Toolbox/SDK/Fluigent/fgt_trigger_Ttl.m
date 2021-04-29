function varargout = fgt_trigger_Ttl( TtlIndex )
%FGT_TRIGGER_TTL Trigger a specific TTL port if it is in output mode.
% 
% fgt_trigger_Ttl(TtlIndex) sends a TTL pulse on the specified port, if it
% is configured in an output mode. The pulse will be a rising edge or a
% falling edge according to the mode that was set.
%
% error_code = fgt_trigger_Ttl(TtlIndex) also returns the error code
% returned by the library function.
%
% See also:
%     fgt_set_TtlMode

error_code = LowLevel.fgt_trigger_Ttl( TtlIndex );
manage_generic_status('fgt_trigger_Ttl', error_code);
if nargout > 0
    varargout = {fgt_ERROR_CODE(error_code)};
end
end

