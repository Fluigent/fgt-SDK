set(program_name "BasicSensorRegulation")
add_executable(${program_name} "Basic Sensor Regulation.cpp")
target_link_libraries(${program_name} PRIVATE fgt_SDK_cpp)
COPY_SDK_LIB(${program_name})