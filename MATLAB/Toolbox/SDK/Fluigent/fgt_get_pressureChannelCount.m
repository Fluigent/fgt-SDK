function [ nbPChan, error_code ] = fgt_get_pressureChannelCount( )
%FGT_GET_PRESSURECHANNELCOUNT Get total number of initialized pressure channels. 
% 
% nbPChan = fgt_get_pressureChannelCount returns the total number of
% pressure channels.
% It is the sum of all MFCS, MFCS-EZ and Flow EZ pressure controllers.
%
% [ nbPChan, error_code ] = fgt_get_pressureChannelCount( ) also returns
% the error code returned by the library function
%
% See also:
%     fgt_get_pressureChannelsInfo

[error_code, nbPChan]= LowLevel.fgt_get_pressureChannelCount();
manage_generic_status('fgt_get_pressureChannelCount', error_code);
error_code = fgt_ERROR_CODE(error_code);
end

