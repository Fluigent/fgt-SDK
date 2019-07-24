function [ nbQChan ] = fgt_get_sensorChannelCount( )
%FGT_GET_SENSORCHANNELCOUNT Get total number of initialized sensor channels. 
% 
% nbPChan = fgt_get_pressureChannelCount returns the total number of
% pressure channels.
% It is the sum of all connected Flow Units on Flowboard and Flow EZ
%
% See also:
%     fgt_get_sensorChannelsInfo


[error_code, nbQChan] = LowLevel.fgt_get_sensorChannelCount();
manage_generic_status('fgt_get_sensorChannelCount', error_code);
end

