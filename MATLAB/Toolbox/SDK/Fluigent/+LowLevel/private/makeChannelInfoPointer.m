function [ pointerToStruct ] = makeChannelInfoPointer(  )
%MAKECHANNELINFOPOINTER Create libpointer of fgt_CHANNEL_INFO to be passed to DLL

info_array = makeChannelInfoStruct;
pointerToStruct = libpointer('fgt_CHANNEL_INFO', info_array);
clear info_array
end

