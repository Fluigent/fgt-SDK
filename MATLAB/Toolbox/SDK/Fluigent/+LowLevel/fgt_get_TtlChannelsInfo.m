function [ error_code, info_array ] = fgt_get_TtlChannelsInfo( )
%FGT_GET_TTLCHANNELSINFO Summary of this function goes here
%   Detailed explanation goes here
load_fgt
pointerToStruct = makeChannelInfoPointer;
[error_code, ~] = calllib('fgt_sdk', 'fgt_get_TtlChannelsInfo', pointerToStruct);
info_array = extractChannelInfoStruct(pointerToStruct);
clear pointerToStruct
end

