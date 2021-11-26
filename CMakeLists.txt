cmake_minimum_required (VERSION 3.14)

project (LIST_CACHE)

#compiler flags
include (flags/flags.cmake)

add_subdirectory (sources)
message (STATUS "Collected libs: ${LIBLIST}")

foreach(LIB ${LIBLIST})
    target_include_directories (${LIB} PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/headers)
    target_include_directories (${LIB} PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/headers/${LIB})   
endforeach()


add_subdirectory (tools)
message (STATUS "Collected tools: ${TOOLLIST}")

foreach(TOOL ${TOOLLIST})
    target_include_directories(${TOOL} PRIVATE "${PROJECT_BINARY_DIR}")
    target_include_directories (${TOOL} PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/headers)
    target_include_directories (${TOOL} PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/headers/${TOOL})   

    target_link_options(${TOOL} PRIVATE "$<$<CXX_COMPILER_ID:GNU>:$<$<CONFIG:Debug>:${DED_SAN_LST}${DED_GCC_WARNS_LST}>>")
    target_compile_options(${TOOL} PRIVATE "$<$<CXX_COMPILER_ID:GNU>:$<$<CONFIG:Debug>:${DED_SAN_LST}${DED_GCC_WARNS_LST}>>")

    target_compile_features(${TOOL} PRIVATE cxx_std_11)
    
    target_link_libraries(${TOOL} ${LIBLIST})
endforeach()

