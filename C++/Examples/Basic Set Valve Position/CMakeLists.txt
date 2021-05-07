set(program_name "BasicSetValvePosition")
add_executable(${program_name} "Basic Set Valve Position.cpp")
target_link_libraries(${program_name} PRIVATE fgt_SDK_cpp)
COPY_SDK_LIB(${program_name})