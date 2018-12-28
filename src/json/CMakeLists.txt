set(DES_TOOL_SOURCES_json
        ${CMAKE_CURRENT_SOURCE_DIR}/DESFile.cpp
)

set(DES_TOOL_HEADERS_json
        ${CMAKE_CURRENT_SOURCE_DIR}/DESFile.h
)

set(DES_TOOL_SOURCES
        ${DES_TOOL_SOURCES}
        ${DES_TOOL_SOURCES_json}
        PARENT_SCOPE
        )

set(DES_TOOL_HEADERS
        ${DES_TOOL_HEADERS}
        ${DES_TOOL_HEADERS_json}
        PARENT_SCOPE
        )
