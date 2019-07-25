function [SNs, types] = fgt_detect( )
%FGT_DETECT Detect all connected Fluigent instruments
% 
% [SNs, types] = fgt_detect() returns the serial numbers of the detected
% instruments in SNs, and their type codes in types.
% 
% See also:
%     fgt_init

[~, SNs, types] = LowLevel.fgt_detect();
types = fgt_INSTRUMENT_TYPE(types);
end

