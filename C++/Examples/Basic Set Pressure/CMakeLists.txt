set(program_name "BasicSetPressure")
add_executable(${program_name} "Basic Set Pressure.cpp")
target_link_libraries(${program_name} PRIVATE fgt_SDK_cpp)
COPY_SDK_LIB(${program_name})