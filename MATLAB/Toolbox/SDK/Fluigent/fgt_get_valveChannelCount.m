function [ nbVChan, error_code ] = fgt_get_valveChannelCount( )
%FGT_GET_VALVECHANNELCOUNT Get total number of initialized valve channels. 
% 
% nbVChan = fgt_get_valveChannelCount returns the total number of
% valve channels.
% It is the sum of all connected Two-Switch, L-Switch and M-Switch
% valves connected to Switchboard or Switch EZ devices, as well
% as individual P-Switch outputs (8 per device).
%
% [ nbVChan, error_code ] = fgt_get_valveChannelCount( ) also returns the
% error code returned by the library function.
%
% See also:
%     fgt_get_valveChannelsInfo


[error_code, nbVChan] = LowLevel.fgt_get_valveChannelCount();
manage_generic_status('fgt_get_valveChannelCount', error_code);
error_code = fgt_ERROR_CODE(error_code);
end

