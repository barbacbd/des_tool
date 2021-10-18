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



# Find Qt5
file(GLOB Qt5_OPT_DIRS /opt/Qt*/5*[0-9]*[0-9])
file(GLOB Qt5_HOME_DIRS $ENV{HOME}/Qt*/5*[0-9]*[0-9])
foreach(dir ${Qt5_OPT_DIRS} ${Qt5_HOME_DIRS})
    find_path(Qt5_CMAKE_DIR NAMES lib/cmake HINTS ${dir} ${dir}/gcc_64)
    if(Qt5_CMAKE_DIR)
    break() # No need to loop over the rest once we've found the Qt5 cmake directory.
    endif()
endforeach()
if(Qt5_CMAKE_DIR)
    set(CMAKE_PREFIX_PATH ${Qt5_CMAKE_DIR})
    find_package(Qt5 COMPONENTS Widgets Core Network DBus WebEngineWidgets REQUIRED) # Gamepad Sensors
    if (Qt5_FOUND)
        message("-- Found Qt5: ${Qt5_CMAKE_DIR}")
	set(Qt5_LIBRARIES
                ${Qt5Widgets_LIBRARIES}
                ${Qt5Core_LIBRARIES}
                ${Qt5Network_LIBRARIES}
                ${Qt5DBus_LIBRARIES}
			${Qt5WebEngineWidgets_LIBRARIES}) # ${Qt5Gamepad_LIBRARIES} ${Qt5Sensors_LIBRARIES}
        set(Qt5_INCLUDE_DIRS
                ${Qt5Widgets_INCLUDE_DIRS}
                ${Qt5Core_INCLUDE_DIRS}
                ${Qt5Network_INCLUDE_DIRS}
                ${Qt5DBus_INCLUDE_DIRS}
                ${Qt5WebEngineWidgets_INCLUDE_DIRS})# ${Qt5Gamepad_INCLUDE_DIRS} ${Qt5Sensors_INCLUDE_DIRS}
        include_directories(${Qt5_INCLUDE_DIRS})
    endif()
else()
    message(FATAL_ERROR "Unable to locate Qt5 files. Did you install to /opt/Qt?")
endif()



###############################################################################
# Add source directories
###############################################################################
add_subdirectory(src)

set(DES_TOOL_SOURCES
        ${DES_TOOL_SOURCES})
set(DES_TOOL_HEADERS
        ${DES_TOOL_HEADERS})

# Add executables
add_executable(des_tool ${DES_TOOL_SOURCES})

# Link it with the SISCommon and other libraries
target_link_libraries(des_tool ${OTHER_LIBS} ${Qt5_LIBRARIES})

SET_TARGET_PROPERTIES(des_tool
        PROPERTIES
        DEBUG_OUTPUT_NAME des_tool${DEBUG_EXTENSION}
        RELEASE_OUTPUT_NAME des_tool
        )

add_custom_command(
        TARGET des_tool POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy
        ${CMAKE_SOURCE_DIR}/simulations/des.json
        ${CMAKE_CURRENT_BINARY_DIR}/des.json)

install(TARGETS des_tool RUNTIME DESTINATION ${BINDIR})

