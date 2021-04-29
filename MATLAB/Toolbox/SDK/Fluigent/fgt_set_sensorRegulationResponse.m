function varargout = fgt_set_sensorRegulationResponse( sensorIndex, responseTime )
%FGT_SET_SENSORREGULATIONRESPONSE Set on a running regulation pressure response time.
%
% fgt_set_sensorRegulationResponse(sensorIndex, responseTime) sets the
% typical response time in seconds for the regulation on the selected
% sensor.
%
% error_code = fgt_set_sensorRegulationResponse(sensorIndex, responseTime)
% also returns the error code returned by the library function.
%
% Minimal value is 2 for Flow EZ, 6 for MFCS controllers.
% This function is useful if a more smooth response is wanted.

error_code = LowLevel.fgt_set_sensorRegulationResponse( sensorIndex, responseTime );
manage_sensor_status('fgt_set_sensorRegulationResponse', sensorIndex);
if nargout > 0
    varargout = {fgt_ERROR_CODE(error_code)};
end
end

