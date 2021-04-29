function varargout = fgt_init(varargin)
%FGT_INIT Initialize or reinitialize the Fluigent SDK instance. 
% 
% fgt_init initializes all of the detected Fluigent instruments (MFCS,
% MFCS-EZ, FRP, LineUP, IPS). They are then indexed in the order 
% MFCS -> MFCS-EZ -> Flow EZ for the pressure channels
% FRP -> Flow EZ -> IPS for the sensor channels.
% 
% fgt_init(SNs) initializes the instruments whose serial numbers are in the
% array SNs. They are then indexed in the order in which they appear in the
% array.
%
% error_code = fgt_init(...) also returns the error code returned by the
% library function.
%
% This function is optional, directly calling a function will automatically
% create the instance. In this case, all instruments are initialized.
% Only one instance can be opened at once. If called again, the session is 
% reinitialized.

if nargin == 0
    [error_code]= LowLevel.fgt_init();
elseif nargin == 1
    [error_code]= LowLevel.fgt_initEx(varargin{1});
else
    [error_code]= LowLevel.fgt_initEx(cell2mat(varargin));
end
    
manage_generic_status('fgt_init', error_code);
if nargout > 0
    varargout = {fgt_ERROR_CODE(error_code)};
end
end

