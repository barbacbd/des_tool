set(DES_TOOL_SOURCES_tool_components
        )

set(DES_TOOL_HEADERS_tool_components
        ${CMAKE_CURRENT_SOURCE_DIR}/Components.h
        )

set(DES_TOOL_SOURCES
        ${DES_TOOL_SOURCES}
        ${DES_TOOL_SOURCES_tool_components}
        PARENT_SCOPE
        )

set(DES_TOOL_HEADERS
        ${DES_TOOL_HEADERS}
        ${DES_TOOL_HEADERS_tool_components}
        PARENT_SCOPE
        )
