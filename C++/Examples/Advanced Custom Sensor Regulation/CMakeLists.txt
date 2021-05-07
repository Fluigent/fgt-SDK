set(program_name "AdvancedCustomSensorRegulation")
add_executable(${program_name} "Advanced Custom Sensor Regulation.cpp")
target_link_libraries(${program_name} PRIVATE fgt_SDK_cpp)
COPY_SDK_LIB(${program_name})
