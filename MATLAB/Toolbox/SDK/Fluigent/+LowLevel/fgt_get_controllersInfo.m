function [error_code, info_array] = fgt_get_controllersInfo( )
%FGT_GET_CONTROLLERSINFO Summary of this function goes here
%   Detailed explanation goes here
load_fgt
SN = num2cell(zeros(256,1, 'uint16'));
Firmware = num2cell(zeros(256,1, 'uint16'));
id = num2cell(zeros(256,1, 'uint32'));
InstrType = num2cell(zeros(256,1, 'uint32'));

info_array = struct(...
    'SN', SN,...
    'Firmware', Firmware,...
    'id', id,...
    'InstrType', InstrType);

pointerToStruct = libpointer('fgt_CONTROLLER_INFO', info_array);
[error_code, ~] = calllib('fgt_sdk', 'fgt_get_controllersInfo', pointerToStruct);
for i=0:255
    offsetPointer = pointerToStruct+(i);
    if(offsetPointer.Value.SN == 0)
        break;
    end
    info_array(i+1) = offsetPointer.Value;
end
info_array = info_array(1:i);
clear offsetPointer pointerToStruct
end