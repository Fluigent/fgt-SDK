function [ infoArray ] = fgt_get_pressureChannelsInfo( )
%FGT_GET_PRESSURECHANNELSINFO Retrieve information about initialized pressure channels.
% 
% 
% infoArray = fgt_get_pressureChannelsInfo() returns a structure array
% containing the following fields for each pressure channel:
%
% ControllerSN: serial number of the controller
% firmware: firmware version
% DeviceSN: serial number of the channel, if applicable
% position: index of the channel within the controller
% index: global index of the channel across all instruments
% indexID: instrument's unique identifier
% InstrType: type of instrument
%
% This function is useful in order to get channels order, controller, 
% unique ID and instrument type.
% By default this array is built with MFCS first, MFCS-EZ second and 
% Flow EZ last. 
% If only one instrument is used, index is the default channel indexing 
% starting at 0.
% You can initialize instruments in specific order by passing the serial
% numbers to fgt_init.

[error_code, infoArray]= LowLevel.fgt_get_pressureChannelsInfo();
for i=1:numel(infoArray)
    infoArray(i).InstrType = fgt_INSTRUMENT_TYPE(infoArray(i).InstrType);
end
manage_generic_status('fgt_get_pressureChannelsInfo', error_code);
end