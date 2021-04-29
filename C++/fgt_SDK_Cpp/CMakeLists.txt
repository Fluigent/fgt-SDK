add_library(fgt_SDK SHARED IMPORTED)

if(WIN32)
    set(TARGET_ARCHITECTURE ${CMAKE_CXX_COMPILER_ARCHITECTURE_ID})
	if(${TARGET_ARCHITECTURE} STREQUAL "X86")
		set_property(TARGET fgt_SDK PROPERTY IMPORTED_LOCATION ${CMAKE_CURRENT_SOURCE_DIR}/dlls/windows/x86/fgt_SDK.dll)
		set_property(TARGET fgt_SDK PROPERTY IMPORTED_IMPLIB ${CMAKE_CURRENT_SOURCE_DIR}/dlls/windows/x86/fgt_SDK.lib)
	elseif(${TARGET_ARCHITECTURE} STREQUAL "x64")
		set_property(TARGET fgt_SDK PROPERTY IMPORTED_LOCATION ${CMAKE_CURRENT_SOURCE_DIR}/dlls/windows/x64/fgt_SDK.dll)
		set_property(TARGET fgt_SDK PROPERTY IMPORTED_IMPLIB ${CMAKE_CURRENT_SOURCE_DIR}/dlls/windows/x64/fgt_SDK.lib)
	else()
		message(FATAL_ERROR "Architecture ${TARGET_ARCHITECTURE} not supported")
	endif()
elseif(UNIX AND NOT APPLE)
	 set_property(TARGET fgt_SDK PROPERTY IMPORTED_LOCATION ${CMAKE_CURRENT_SOURCE_DIR}/dlls/linux/x64/libfgt_SDK.so)
elseif(APPLE)
	 set_property(TARGET fgt_SDK PROPERTY IMPORTED_LOCATION ${CMAKE_CURRENT_SOURCE_DIR}/dlls/mac/x64/libfgt_SDK.dylib)
else()
	message(FATAL_ERROR "OS ${CMAKE_SYSTEM_NAME} not supported")
endif()

get_property(SDK_LIBRARY_PATH TARGET fgt_SDK PROPERTY IMPORTED_LOCATION)
set(SDK_LIBRARY_PATH ${SDK_LIBRARY_PATH} PARENT_SCOPE)

function(copy_sdk_lib project_name)
	add_custom_command(TARGET ${project_name} POST_BUILD
					   COMMAND ${CMAKE_COMMAND} -E copy
						  ${SDK_LIBRARY_PATH} $<TARGET_FILE_DIR:${project_name}>)
endfunction()

add_library(fgt_SDK_cpp INTERFACE)
target_sources(fgt_SDK_cpp INTERFACE fgt_SDK_Cpp.cpp)
target_include_directories(fgt_SDK_cpp INTERFACE
    ${CMAKE_CURRENT_SOURCE_DIR}
    ${CMAKE_CURRENT_SOURCE_DIR}/dlls)
target_link_libraries(fgt_SDK_cpp INTERFACE fgt_SDK)