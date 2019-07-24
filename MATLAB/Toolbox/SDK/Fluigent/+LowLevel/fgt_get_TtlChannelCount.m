function [ error_code, nbTtlChan ] = fgt_get_TtlChannelCount( )
%FGT_GET_TTLCHANNELCOUNT Summary of this function goes here
%   Detailed explanation goes here
load_fgt
nbTtlChan = 0;
[error_code, nbTtlChan] = calllib('fgt_sdk', 'fgt_get_TtlChannelCount', nbTtlChan);

end

