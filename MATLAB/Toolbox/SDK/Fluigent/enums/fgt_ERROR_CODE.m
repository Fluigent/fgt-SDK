classdef fgt_ERROR_CODE < uint8
    %FGT_ERROR_CODE Error states reported by the SDK
    
    enumeration
        OK (0),
        USB_error (1),
        Wrong_command (2),
        No_module_at_index (3),
        Wrong_module (4),
        Module_is_sleep (5),
        Master_error (6),
        Failed_init_all_instr (7),
        Wrong_parameter (8),
        Overpressure (9),
        Underpressure (10),
        No_instr_found (11),
        No_modules_found (12),
        No_pressure_controller_found (13),
        Calibrating (14),
        Dll_dependency_error (15),
        Processing (16)
    end
    
    properties
    end
    
    methods
    end
    
end

