function varargout = fgt_get_sensorAirBubbleFlag( sensorIndex )
%FGT_GET_SENSORAIRBUBBLEFLAG Read the air bubble detected flag from a Flow Unit
%
% flag = fgt_get_sensorAirBubbleFlag( sensorIndex ) 1 if an air bubble was 
% detected, 0 otherwise. Only available for Flow Unit ranges M+ and L+.
%
% [flag, error_code] = fgt_get_sensorAirBubbleFlag( sensorIndex )
% also returns the error code returned by the library function.

[error_code, bubble_flag] = LowLevel.fgt_get_sensorAirBubbleFlag(sensorIndex);
manage_sensor_status('fgt_get_sensorAirBubbleFlag', sensorIndex);
error_code = fgt_ERROR_CODE(error_code);
varargout = {bubble_flag, error_code};
end

