function [ info_array ] = extractChannelInfoStruct( pointerToStruct )
%EXTRACTCHANNELINFOSTRUCT Get the channel info struct from the pointer

info_array = makeChannelInfoStruct;
for i=0:255
    offsetPointer = pointerToStruct+(i);
    if(offsetPointer.Value.ControllerSN == 0)
        break;
    end
    info_array(i+1) = offsetPointer.Value;
end
clear offsetPointer;
info_array = info_array(1:i);
end

