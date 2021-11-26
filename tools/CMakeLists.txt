set (
    TOOLLIST
    main
    tests
)

foreach (TOOL ${TOOLLIST})
    add_subdirectory(${TOOL})
endforeach()

set (TOOLLIST "${TOOLLIST}" PARENT_SCOPE)
