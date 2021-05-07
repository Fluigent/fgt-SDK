function [infoArray, typeArray, error_code] = fgt_get_valveChannelsInfo( )
%FGT_GET_VALVECHANNELSINFO Retrieve information about initialized valve channels.
% 
% infoArray = fgt_get_valveChannelsInfo returns a structure array
% containing the following fields for each valve channel:
%
% ControllerSN: serial number of the controller
% firmware: firmware version
% DeviceSN: serial number of the channel, if applicable
% position: index of the channel within the controller
% index: global index of the channel across all instruments
% indexID: instrument's unique identifier
% InstrType: type of instrument
%
% [infoArray, typeArray] = fgt_get_valveChannelsInfo also returns the
% type of each valve in the list, in the same order as infoArray
%
% [infoArray, typeArray, error_code] = fgt_get_valveChannelsInfo() also 
% returns the error code returned by the library function
%
% This function is useful in order to get channels order, controller, 
% unique ID and instrument type.
%
% You can initialize instruments in specific order by passing the serial
% numbers to fgt_init.

[error_code, infoArray, typeArray] = LowLevel.fgt_get_valveChannelsInfo();
for i=1:numel(infoArray)
    infoArray(i).InstrType = fgt_INSTRUMENT_TYPE(infoArray(i).InstrType);
    typeArray(i) = fgt_VALVE_TYPE(typeArray(i));
end
manage_generic_status('fgt_get_valveChannelsInfo', error_code);
error_code = fgt_ERROR_CODE(error_code);
end

