add_subdirectory(json)

set(DES_TOOL_SOURCES
        ${CMAKE_CURRENT_SOURCE_DIR}/main.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/MainWindow.cpp
)

set(DES_TOOL_HEADERS
        ${CMAKE_CURRENT_SOURCE_DIR}/MainWindow.h
)

set(DES_TOOL_SOURCES
        ${DES_TOOL_SOURCES}
        PARENT_SCOPE
        )

set(DES_TOOL_HEADERS
        ${DES_TOOL_HEADERS}
        PARENT_SCOPE
        )