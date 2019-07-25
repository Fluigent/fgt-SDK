function [] = fgt_set_pressureResponse( pressureIndex, value )
%FGT_SET_PRESSURERESPONSE Set pressure controller response. 
% 
% fgt_set_pressureResponse(pressureIndex, value) sets the channel's
% response type to the specified value. 
%
% This function can be used to customise response time for your setup.
% For Flow EZ available values are 0 (use of fast switch valves) or 
% 1 (do not use fast switch valves). Default value is 0.
% For MFCS available values are from 1 to 255. The higher the value, 
% the longer the response time. Default value is 5.

LowLevel.fgt_set_pressureResponse( pressureIndex, value );
manage_pressure_status('fgt_set_pressureResponse', pressureIndex);
end

