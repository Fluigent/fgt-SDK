classdef fgt_SENSOR_TYPE < uint8
    %FGT_SENSOR_TYPE Fluigent sensor available types and ranges
    
    enumeration
        None (0), 
        Flow_XS_single (1),
        Flow_S_single (2),
        Flow_S_dual (3), 
        Flow_M_single (4), 
        Flow_M_dual (5),
        Flow_L_single (6), 
        Flow_L_dual (7), 
        Flow_XL_single (8),
        Pressure_S (9),
        Pressure_M (10),
        Pressure_XL (11),
        Flow_M_plus_dual (12),
        Flow_L_plus_dual (13),
        Flow_L_CFU(14),
        Flow_L_NIFS(15),
    end
    
    properties
    end
    
    methods
    end
    
end

