function [ error_code, nbValveChan ] = fgt_get_valveChannelCount( )
%FGT_GET_VALVECHANNELCOUNT Summary of this function goes here
%   Detailed explanation goes here
load_fgt
nbValveChan = 0;
[error_code, nbValveChan] = calllib('fgt_sdk', 'fgt_get_valveChannelCount', nbValveChan);

end

