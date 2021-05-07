function [ nbQChan, error_code ] = fgt_get_sensorChannelCount( )
%FGT_GET_SENSORCHANNELCOUNT Get total number of initialized sensor channels. 
% 
% nbQChan = fgt_get_sensorChannelCount returns the total number of
% pressure channels.
% It is the sum of all connected Flow Units on Flowboard and Flow EZ,
% and IPS modules.
%
% [ nbQChan, error_code ] = fgt_get_sensorChannelCount( ) also returns the
% error code returned by the library function
%
% See also:
%     fgt_get_sensorChannelsInfo


[error_code, nbQChan] = LowLevel.fgt_get_sensorChannelCount();
manage_generic_status('fgt_get_sensorChannelCount', error_code);
error_code = fgt_ERROR_CODE(error_code);
end

