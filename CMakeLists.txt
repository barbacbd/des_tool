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
set(OTHER_LIBS "-lrt -ldl -lpthread")

###############################################################################
# QT 5.11 Specific Setup
###############################################################################
# Find includes in corresponding build directories
set(CMAKE_INCLUDE_CURRENT_DIR ON)
# Instruct CMake to run moc automatically when needed.
set(CMAKE_AUTOMOC ON)

###############################################################################
#
###############################################################################
SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -g -Wno-deprecated-declarations")

###############################################################################
# The path to cmake modules
# A customized module is used to produce version numbers from Git.
###############################################################################
set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_SOURCE_DIR}/cmake/modules")
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
add_subdirectory(src)

###############################################################################
# Locate and include required dependencies
###############################################################################
# Find assorted dependencies with default cmake files
find_package(Git REQUIRED)

# Find Boost
set(BOOST_ROOT /usr/local) # Preferred installation prefix
find_package(Boost ${BOOST_MIN_VERSION} COMPONENTS system filesystem program_options thread date_time chrono regex REQUIRED)
if(NOT Boost_FOUND)
    message(FATAL_ERROR "Unable to locate Boost 1.53.0")
endif()
include_directories(${Boost_INCLUDE_DIR})

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
    find_package(Qt5 COMPONENTS Widgets Gui Core Network REQUIRED) # Gamepad WebEngineWidgets Sensors
    if (Qt5_FOUND)
        message("-- Found Qt5: ${Qt5_CMAKE_DIR}")
        set(Qt5_LIBRARIES ${Qt5Widgets_LIBRARIES} ${Qt5GUI_LIBRARIES} ${Qt5Core_LIBRARIES} ${Qt5Network_LIBRARIES})
        set(Qt5_INCLUDE_DIRS ${Qt5Widgets_INCLUDE_DIRS} ${Qt5GUI_INCLUDE_DIRS} ${Qt5Core_INCLUDE_DIRS} ${Qt5Network_INCLUDE_DIRS})
        include_directories(${Qt5_INCLUDE_DIRS})
    endif()
else()
    message(FATAL_ERROR "Unable to locate Qt5 files. Did you install to /opt/Qt?")
endif()

set(Boost_USE_STATIC_LIBS OFF)
set(Boost_USE_MULTITHREADED ON)
set(Boost_USE_STATIC_RUNTIME OFF)

set(DES_TOOL_SOURCES
        ${DES_TOOL_SOURCES})
set(DES_TOOL_HEADERS
        ${DES_TOOL_HEADERS})

# Add executables
add_executable(des_tool ${DES_TOOL_SOURCES})

# Link it with the SISCommon and other libraries
target_link_libraries(des_tool ${Qt5_LIBRARIES} ${Boost_LIBRARIES} ${OTHER_LIBS}
        )

SET_TARGET_PROPERTIES(des_tool
        PROPERTIES
        DEBUG_OUTPUT_NAME des_tool${DEBUG_EXTENSION}
        RELEASE_OUTPUT_NAME des_tool
        )

install(TARGETS des_tool RUNTIME DESTINATION ${BINDIR})
