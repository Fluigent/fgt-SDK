function [infoArray, error_code] = fgt_get_controllersInfo( )
%FGT_GET_CONTROLLERSINFO Retrieve information about session controllers. 
% 
% infoArray = fgt_get_controllersInfo() returns a structure array
% containing the following fields for each controller:
%
% SN: serial number
% Firmware: firmware version
% id: identifier
% InstrType: type of Fluigent instrument
%
% [infoArray, error_code] = fgt_get_controllersInfo() also returns the
% error code returned by the library function
%
% Controllers are MFCS, Flowboard, Link, and IPS.

[error_code, infoArray] = LowLevel.fgt_get_controllersInfo;
for i=1:numel(infoArray)
    infoArray(i).InstrType = fgt_INSTRUMENT_TYPE(infoArray(i).InstrType);
end
manage_generic_status('fgt_get_controllersInfo', error_code);
error_code = fgt_ERROR_CODE(error_code);
end