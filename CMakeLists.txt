### CMake file for cyan 
###
###     Author : glaconbleu@codices.org
###
###############################################################################


cmake_minimum_required (VERSION 2.6)

project (cyan_fileio)
set (cyan_fileio_VERSION_MAJOR 0)
set (cyan_fileio_VERSION_MINOR 1)
set (cyan_fileio_VERSION_PATCH 1)
set (cyan_fileio_VERSION_STRING
	${cyan_fileio_VERSION_MAJOR}.${cyan_fileio_VERSION_MINOR}.${cyan_fileio_VERSION_PATCH} )

set( CMAKE_LIBRARY_PATH ${CMAKE_LIBRARY_PATH} /lib /usr/lib /usr/local/lib )
set( CMAKE_INCLUDE_PATH ${CMAKE_INCLUDE_PATH} /usr/include /usr/local/include )
set( CMAKE_MODULE_PATH  ${CMAKE_MODULE_PATH} "${PROJECT_SOURCE_DIR}/cmake" ) 

set ( INSTALL_BIN_PATH bin )
set ( INSTALL_LIB_PATH lib )
set ( INSTALL_AR_PATH  lib )
set ( INSTALL_HEADERS_PATH include )

# Make relative paths absolute (needed later on)

foreach(p LIB BIN HEADERS AR)
        set(var INSTALL_${p}_PATH)
        if(NOT IS_ABSOLUTE "${${var}}")
                set(${var} "${CMAKE_INSTALL_PREFIX}/${${var}}")
        endif()
endforeach()

### Options ###

option(BUILD_TEST   "Build cyan_fileio tests" ON)
option(BUILD_TOOLS "Build and install cyan_fileio tools" ON)
option(BUILD_PNG    "Link PNG library" ON)
###Search for libpng
if(BUILD_PNG)
	find_package(PNG)
endif()

find_package(CYAN) 
### Config File

configure_file ( "${PROJECT_SOURCE_DIR}/config.h.in"
		         "${PROJECT_SOURCE_DIR}/include/cyan_fileio/config/cyan_fileio.h" )

### Set include directories 
        
include_directories( "${CMAKE_CURRENT_SOURCE_DIR}/include/"
	                 "${CMAKE_CURRENT_BINARY_DIR}" 
		) 

if(CYAN_FOUND)
	message("SUCCESS: cyan was found in ${CYAN_INCLUDE_DIR}")
	include_directories( "${CYAN_INCLUDE_DIR}")
else()
	message("ERROR: cyan was not found")
endif()

if (PNG_FOUND)
	include_directories( "${PNG_INCLUDE_DIRS}")
else()
	message("libpng couldn't be found.")
endif()

### File lists

file( GLOB src  "src/*.c" )


file( GLOB hdr         "include/cyan_fileio/*.h"  )

### Targets

add_library( "cyan_fileio" SHARED ${src} ) 

set_target_properties(cyan_fileio PROPERTIES VERSION ${cyan_fileio_VERSION_STRING}
                                    SOVERSION ${cyan_fileio_VERSION_MAJOR})

### Linking

target_link_libraries( "cyan_fileio" "m" )
if (CYAN_FOUND)
	message("Linking cyan library located at : ${CYAN_LIBRARY}")
	target_link_libraries( "cyan_fileio" ${CYAN_LIBRARY})
endif()

if (PNG_FOUND)
	target_link_libraries( "cyan_fileio" ${PNG_LIBRARIES})
endif()


### Cmake file

configure_file(cyan_fileio-config.cmake.in "${PROJECT_BINARY_DIR}/cyan_fileio-config.cmake" @ONLY)

install ( FILES "${PROJECT_BINARY_DIR}/cyan_fileio-config.cmake" 
      DESTINATION "${INSTALL_LIB_PATH}/cyan_fileio" COMPONENT dev )  

configure_file(cyan_fileio-configVersion.cmake.in
	"${PROJECT_BINARY_DIR}/cyan_fileio-configVersion.cmake" @ONLY)

install ( FILES "${PROJECT_BINARY_DIR}/cyan_fileio-configVersion.cmake" 
      DESTINATION "${INSTALL_LIB_PATH}/cyan_fileio" COMPONENT dev )  

### Install 

install( TARGETS "cyan_fileio"
	    RUNTIME DESTINATION "${INSTALL_BIN_PATH}/cyan_fileio"  COMPONENT main
	    LIBRARY DESTINATION "${INSTALL_LIB_PATH}/cyan_fileio"  COMPONENT main
	    ARCHIVE DESTINATION ${INSTALL_AR_PATH}   COMPONENT main )	##TODO I don't know what is the archive, so i didn't
    									##modify destination to "cyan_fileio"

install( FILES ${hdr}
	    DESTINATION ${INSTALL_HEADERS_PATH}/cyan_fileio/${name} 
	    COMPONENT main )

### Build tools
if(BUILD_TOOLS)
	add_subdirectory(tools)
endif()

# Regression tests

if (BUILD_TEST)
    enable_testing()
    add_subdirectory(test)
endif()

### Pretty Display :

MESSAGE(STATUS "*********************************************************")
MESSAGE(STATUS "")
MESSAGE(STATUS "Build type:        " ${CMAKE_BUILD_TYPE})
MESSAGE(STATUS "")
MESSAGE(STATUS "ENABLE_LIBPNG:      " ${BUILD_PNG})
MESSAGE(STATUS "BUILD_TOOLS:        " ${BUILD_TOOLS})
MESSAGE(STATUS "BUILD_TEST:        " ${BUILD_TEST})
MESSAGE(STATUS "")
MESSAGE(STATUS "*********************************************************")
