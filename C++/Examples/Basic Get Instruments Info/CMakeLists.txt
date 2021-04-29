set(program_name "BasicGetInstrumentsInfo")
add_executable(${program_name} "Basic Get Instruments Info.cpp")
target_link_libraries(${program_name} PRIVATE fgt_SDK_cpp)
COPY_SDK_LIB(${program_name})
