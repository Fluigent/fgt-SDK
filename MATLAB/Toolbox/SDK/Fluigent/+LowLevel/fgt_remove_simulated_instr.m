function [ error_code ] = fgt_remove_simulated_instr(type, serial)
%FGT_REMOVE_SIMULATED_INSTR Remove simulated instrument
load_fgt
error_code = calllib('fgt_sdk', 'fgt_remove_simulated_instr', type, serial);
end

