set(DES_TOOL_SOURCES_tool_ui
        ${CMAKE_CURRENT_SOURCE_DIR}/MainWidget.cpp
        )

set(DES_TOOL_HEADERS_tool_ui
        ${CMAKE_CURRENT_SOURCE_DIR}/MainWidget.h
        )

set(DES_TOOL_SOURCES
        ${DES_TOOL_SOURCES}
        ${DES_TOOL_SOURCES_tool_ui}
        PARENT_SCOPE
        )

set(DES_TOOL_HEADERS
        ${DES_TOOL_HEADERS}
        ${DES_TOOL_HEADERS_tool_ui}
        PARENT_SCOPE
        )
