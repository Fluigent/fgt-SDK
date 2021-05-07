set(program_name "BasicReadSensorData")
add_executable(${program_name} "Basic Read Sensor Data.cpp")
target_link_libraries(${program_name} PRIVATE fgt_SDK_cpp)
COPY_SDK_LIB(${program_name})