###############################################################################
# Project Name
###############################################################################
project(DESTool)

###############################################################################
# Minimum supported CMake version
###############################################################################
cmake_minimum_required(VERSION 2.8.11)

###############################################################################
# Include developer's personalized settings
###############################################################################
set(OTHER_LIBS "-lrt -ldl -lpthread -lglut -lGL -lGLU -lglut -lm")

# Find includes in corresponding build directories
set(CMAKE_INCLUDE_CURRENT_DIR ON)
# Instruct CMake to run moc automatically when needed.
set(CMAKE_AUTOMOC ON)

###############################################################################
#
###############################################################################
SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -g -Wno-deprecated-declarations")

###############################################################################
# The installation prefix
# This is where installed files will go.
# On WIN32, this will automatically be prefixed with drive letter.
###############################################################################
if(${RPM})
    set(CMAKE_INSTALL_PREFIX "/usr")
    set(LIBDIR "/usr/lib64") # Installs to lib64 on CentOS.
else()
    set(CMAKE_INSTALL_PREFIX "/devel/install")
    set(LIBDIR "/devel/install/lib") # Installs to lib on Ubuntu.
endif()
set(BINDIR "${CMAKE_INSTALL_PREFIX}/bin")
include_directories("${CMAKE_INSTALL_PREFIX}/include")
link_directories(${LIBDIR})

###############################################################################
# Add source directories
###############################################################################
add_subdirectory(opengl)

set(DES_TOOL_SOURCES
        ${DES_TOOL_SOURCES})
set(DES_TOOL_HEADERS
        ${DES_TOOL_HEADERS})

# Add executables
add_executable(des_tool ${DES_TOOL_SOURCES})

# Link it with the SISCommon and other libraries
target_link_libraries(des_tool ${OTHER_LIBS})

SET_TARGET_PROPERTIES(des_tool
        PROPERTIES
        DEBUG_OUTPUT_NAME des_tool${DEBUG_EXTENSION}
        RELEASE_OUTPUT_NAME des_tool
        )

add_custom_command(
        TARGET des_tool POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy
        ${CMAKE_SOURCE_DIR}/simulations/des.txt
        ${CMAKE_CURRENT_BINARY_DIR}/des.txt)

install(TARGETS des_tool RUNTIME DESTINATION ${BINDIR})

