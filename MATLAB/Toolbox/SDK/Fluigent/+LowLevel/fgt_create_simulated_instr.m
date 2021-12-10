function [ error_code ] = fgt_create_simulated_instr(type, serial, version, config)
%FGT_CREATE_SIMULATED_INSTR Create simulated instrument
load_fgt
length = numel(config);
error_code = calllib('fgt_sdk', 'fgt_create_simulated_instr', type, serial, version, config, length);
end

