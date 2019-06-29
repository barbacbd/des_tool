set(DES_TOOL_SOURCES_tool_simulation
        ${CMAKE_CURRENT_SOURCE_DIR}/Simulation.cpp
        )

set(DES_TOOL_HEADERS_tool_simulation
        ${CMAKE_CURRENT_SOURCE_DIR}/Simulation.h
        )

set(DES_TOOL_SOURCES
        ${DES_TOOL_SOURCES}
        ${DES_TOOL_SOURCES_tool_simulation}
        PARENT_SCOPE
        )

set(DES_TOOL_HEADERS
        ${DES_TOOL_HEADERS}
        ${DES_TOOL_HEADERS_tool_simulation}
        PARENT_SCOPE
        )
