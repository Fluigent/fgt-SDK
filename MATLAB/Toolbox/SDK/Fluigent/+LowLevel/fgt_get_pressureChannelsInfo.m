function [ error_code, info_array ] = fgt_get_pressureChannelsInfo( )
%FGT_GET_PRESSURECHANNELSINFO Summary of this function goes here
%   Detailed explanation goes here
load_fgt
pointerToStruct = makeChannelInfoPointer;
[error_code, ~] = calllib('fgt_sdk', 'fgt_get_pressureChannelsInfo', pointerToStruct);
info_array = extractChannelInfoStruct(pointerToStruct);
clear pointerToStruct
end