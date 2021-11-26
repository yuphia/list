cmake_minimum_required (VERSION 3.14)

project (LIST_CACHE)

#compiler flags
include (flags/flags.cmake)

add_subdirectory (sources)
message (STATUS "Collected libs: ${LIBLIST}")

foreach(LIB ${LIBLIST})
    target_include_directories (${LIB} PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/headers) 
endforeach()


add_subdirectory (tools)
message (STATUS "Collected tools: ${TOOLLIST}")

foreach(TOOL ${TOOLLIST}) 
    if (CMAKE_BUILD_TYPE EQUAL DEBUG)
        target_link_options (${TOOL} PRIVATE "${DED_SAN_LST}")
        target_compile_options (${TOOL} PRIVATE "${DED_SAN}${DED_GCC_WARNS}")
    endif()

    target_compile_features(${TOOL} PRIVATE cxx_std_11)
    
    target_link_libraries(${TOOL} ${LIBLIST})
endforeach()

