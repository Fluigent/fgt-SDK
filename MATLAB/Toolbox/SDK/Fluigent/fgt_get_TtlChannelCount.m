function [ nbTtlChan ] = fgt_get_TtlChannelCount( )
%FGT_GET_TTLCHANNELCOUNT Get total number of initialized TTL channels. 
%  
% nbPChan = fgt_get_pressureChannelCount returns the total number of
% pressure channels.
% It is the sum of all connected Link TTL ports.
% 
% Returns:
%     the total number of initialized TTL channels.

[error_code, nbTtlChan] = LowLevel.fgt_get_TtlChannelCount();
manage_generic_status('fgt_get_TtlChannelCount', error_code);
end

