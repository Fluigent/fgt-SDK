function [nbInstr, SNs, types] = fgt_detect( )
%FGT_DETECT Summary of this function goes here
%   Detailed explanation goes here
load_fgt
SNs = zeros(1,256);
types = zeros(1,256);
[nbInstr, SNs, types] = calllib('fgt_sdk', 'fgt_detect', SNs, types);
SNs = SNs(1:nbInstr);
types = types(1:nbInstr);
end

