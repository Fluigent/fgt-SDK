function [error_code, type, instrSN, infoCode, detail] = fgt_get_sensorStatus( sensorIndex )
%FGT_GET_SENSORSTATUS Summary of this function goes here
%   Detailed explanation goes here
load_fgt
type = 0;
instrSN = 0;
infoCode = uint8(0);
detail = zeros(1,140);
[error_code, type, instrSN, infoCode, detail] = ...
    calllib('fgt_sdk', 'fgt_get_sensorStatus', sensorIndex, ... 
    type, instrSN, infoCode, detail);
detail = strtrim(char(detail(detail ~=0)));
end

