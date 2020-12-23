function [infoArray] = fgt_get_controllersInfo( )
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
% Controllers are MFCS, Flowboard, Link, and IPS.

[error_code, infoArray] = LowLevel.fgt_get_controllersInfo;
for i=1:numel(infoArray)
    infoArray(i).InstrType = fgt_INSTRUMENT_TYPE(infoArray(i).InstrType);
end
manage_generic_status('fgt_get_controllersInfo', error_code);
end