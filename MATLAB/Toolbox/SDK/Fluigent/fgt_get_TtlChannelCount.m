function [ nbTtlChan, error_code ] = fgt_get_TtlChannelCount( )
%FGT_GET_TTLCHANNELCOUNT Get total number of initialized TTL channels. 
%  
% nbTtlChan = fgt_get_TtlChannelCount( ) returns the total number of
% pressure channels.
% It is the sum of all connected Link TTL ports.
%
% [ nbTtlChan, error_code ] = fgt_get_TtlChannelCount( ) also returns the
% error code returned by the library function.
% 
% Returns:
%     the total number of initialized TTL channels.

[error_code, nbTtlChan] = LowLevel.fgt_get_TtlChannelCount();
manage_generic_status('fgt_get_TtlChannelCount', error_code);
error_code = fgt_ERROR_CODE(error_code);
end

