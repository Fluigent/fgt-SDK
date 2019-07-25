function [ ] = fgt_calibratePressure( pressureIndex )
%FGT_CALIBRATEPRESSURE Calibrate internal pressure sensor.
%
% fgt_calibratePressure(pressureIndex) starts calibration on the 
% pressure channel identified by the index or unique ID pressureIndex.
%
% After calibration is finished, 0 pressure value corresponds to
% atmospheric pressure.
%
% During calibration step no pressure order is accepted. 
% Total duration varies from 3 to 8 seconds.

[error_code] = LowLevel.fgt_calibratePressure(pressureIndex);
manage_pressure_status('fgt_calibratePressure', pressureIndex);

end

