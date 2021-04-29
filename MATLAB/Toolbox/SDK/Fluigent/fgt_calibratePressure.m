function varargout = fgt_calibratePressure( pressureIndex )
%FGT_CALIBRATEPRESSURE Calibrate internal pressure sensor.
%
% fgt_calibratePressure(pressureIndex) starts calibration on the 
% pressure channel identified by the index or unique ID pressureIndex.
%
% error_code = fgt_calibratePressure(pressureIndex) also returns the
% error code returned by the library function.
%
% After calibration is finished, 0 pressure value corresponds to
% atmospheric pressure.
%
% During calibration step no pressure order is accepted. 
% Total duration varies from 3 to 8 seconds.

[error_code] = LowLevel.fgt_calibratePressure(pressureIndex);
manage_pressure_status('fgt_calibratePressure', pressureIndex);
if nargout > 0
    varargout = {fgt_ERROR_CODE(error_code)};
end
end

