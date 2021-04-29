function [error_code, info_array, type_array] = fgt_get_valveChannelsInfo( )
%FGT_GET_VALVECHANNELSINFO Summary of this function goes here
%   Detailed explanation goes here
load_fgt
type_array = zeros(256, 1);
pointerToStruct = makeChannelInfoPointer;
[error_code, ~, type_array] = calllib('fgt_sdk', 'fgt_get_valveChannelsInfo', pointerToStruct, type_array);
info_array = extractChannelInfoStruct(pointerToStruct);
type_array = type_array(1:numel(info_array));
clear pointerToStruct
end

