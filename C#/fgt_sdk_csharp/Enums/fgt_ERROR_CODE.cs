namespace fgt_sdk.Enums
{
    /// <summary>
    /// Returned error codes from dll functions
    /// </summary>
    public enum fgt_ERROR_CODE
    {
        /// No error
        OK,
        /// USB communication error
        USB_error,
        /// Wrong command was sent
        Wrong_command,
        /// There is no module initialized at selected index
        No_module_at_index,
        /// Wrong module was selected, unavailable feature
        Wrong_module,
        /// Module is in sleep mode, orders are not taken into account
        Module_is_sleep,
        /// Controller error
        Master_error,
        /// Some instruments failed to initialize
        Failed_init_all_instr,
        /// Function parameter is not correct or out of the bounds
        Wrong_parameter,
        /// Pressure module is in overpressure protection
        Overpressure,
        /// Pressure module is in underpressure protection
        Underpressure,
        /// No Fluigent instrument was found
        No_instr_found,
        /// No Fluigent pressure or sensor module was found
        No_modules_found,
        /// No Fluigent pressure controller was found
        No_pressure_controller_found,
        /// Pressure or sensor module is calibrating, read value may be incorrect
        Calibrating,
        /// Some dependencies are not found
        Dll_dependency_error,
        /// M-Switch is still processing the last input
        Processing,
    }
}