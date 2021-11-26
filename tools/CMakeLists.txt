set (
    TOOLS
    main
    tests
)

foreach (TOOL ${TOOLS})
    add_subdirectory(${TOOL})
endforeach()

set (TOOLLIST "${TOOLLIST}" PARENT_SCOPE)