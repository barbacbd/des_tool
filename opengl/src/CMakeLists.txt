set(DES_TOOL_SOURCES_src
        ${CMAKE_CURRENT_SOURCE_DIR}/button.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/draw.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/geometry.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/main.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/printStructs.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/readWriteFile.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/Simulate.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/statistics.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/utility.cpp
        )

set(DES_TOOL_HEADERS_src
        ${CMAKE_CURRENT_SOURCE_DIR}/button.h
        ${CMAKE_CURRENT_SOURCE_DIR}/Common.h
        ${CMAKE_CURRENT_SOURCE_DIR}/draw.h
        ${CMAKE_CURRENT_SOURCE_DIR}/geometry.h
        ${CMAKE_CURRENT_SOURCE_DIR}/main.h
        ${CMAKE_CURRENT_SOURCE_DIR}/printStructs.h
        ${CMAKE_CURRENT_SOURCE_DIR}/readWriteFile.h
        ${CMAKE_CURRENT_SOURCE_DIR}/Simulate.h
        ${CMAKE_CURRENT_SOURCE_DIR}/states.h
        ${CMAKE_CURRENT_SOURCE_DIR}/statistics.h
        ${CMAKE_CURRENT_SOURCE_DIR}/utility.h
        )

set(DES_TOOL_SOURCES
        ${DES_TOOL_SOURCES_src}
        PARENT_SCOPE
        )

set(DES_TOOL_HEADERS
        ${DES_TOOL_HEADERS_src}
        PARENT_SCOPE
        )