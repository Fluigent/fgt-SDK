function [] = fgt_init(varargin)
%FGT_INIT Initialize or reinitialize the Fluigent SDK instance. 
% 
% fgt_init initializes all of the detected Fluigent instruments (MFCS,
% MFCS-EZ, FRP, LineUP). They are then indexed in the order MFCS -> MFCS-EZ
% -> Flow EZ for the pressure channels, and FRP -> Flow EZ for the flow
% rate channels.
% 
% fgt_init(SNs) initializes the instruments whose serial numbers are in the
% array SNs. They are then indexed in the order i which they appear in the
% array.
%
% This function is optional, directly calling a function will automatically
% create the instance. In this case, all instruments are initialized.
% Only one instance can be opened at once. If called again, session is 
% reinitialized.

if nargin == 0
    [error_code]= LowLevel.fgt_init();
elseif nargin == 1
    [error_code]= LowLevel.fgt_initEx(varargin{1});
else
    [error_code]= LowLevel.fgt_initEx(cell2mat(varargin));
end
    
manage_generic_status('fgt_init', error_code);
end

