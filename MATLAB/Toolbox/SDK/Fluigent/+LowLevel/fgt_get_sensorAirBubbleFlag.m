function [error_code, bubble_flag] = fgt_get_sensorAirBubbleFlag( sensorIndex )
%fgt_get_sensorAirBubbleFlag Summary of this function goes here
%   Detailed explanation goes here
load_fgt
bubble_flag = 0;
[error_code, bubble_flag] = calllib('fgt_sdk', 'fgt_get_sensorAirBubbleFlag', sensorIndex, bubble_flag);

end

