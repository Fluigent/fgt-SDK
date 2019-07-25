function [ error_code, nbQChan ] = fgt_get_sensorChannelCount( )
%FGT_GET_SENSORCHANNELCOUNT Summary of this function goes here
%   Detailed explanation goes here
load_fgt
nbQChan = 0;
[error_code, nbQChan] = calllib('fgt_sdk', 'fgt_get_sensorChannelCount', nbQChan);

end

