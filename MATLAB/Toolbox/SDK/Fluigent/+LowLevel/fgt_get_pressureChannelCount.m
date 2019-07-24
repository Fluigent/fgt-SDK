function [ error_code, nbPChan ] = fgt_get_pressureChannelCount( )
%FGT_GET_PRESSURECHANNELCOUNT Summary of this function goes here
%   Detailed explanation goes here
load_fgt
nbPChan = 0;
[error_code, nbPChan] = calllib('fgt_sdk', 'fgt_get_pressureChannelCount', nbPChan);

end

