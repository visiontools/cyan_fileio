### CMake file for cyan 
###
###     Author : glaconbleu@codices.org
###
###############################################################################


cmake_minimum_required (VERSION 2.6)

project (cyan_fileio)
set (cyan_fileio_VERSION_MAJOR 0)
set (cyan_fileio_VERSION_MINOR 1)
set (cyan_fileio_VERSION_PATCH 0)
set (cyan_fileio_VERSION
	"${cyan_fileio_VERSION_MAJOR}.${cyan_fileio_VERSION_MINOR}.${cyan_fileio_VERSION_PATCH}" )

set( CMAKE_LIBRARY_PATH ${CMAKE_LIBRARY_PATH} /lib /usr/lib /usr/local/lib )
set( CMAKE_INCLUDE_PATH ${CMAKE_INCLUDE_PATH} /usr/include /usr/local/include )
set( CMAKE_MODULE_PATH  ${CMAKE_MODULE_PATH} "${PROJECT_SOURCE_DIR}/cmake" ) 

set ( INSTALL_BIN_PATH /usr/local/bin )
set ( INSTALL_LIB_PATH /usr/local/lib )
set ( INSTALL_AR_PATH  /usr/local/lib )
set ( INSTALL_HEADERS_PATH /usr/local/include )

set( CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -Wl,-rpath -Wl,/usr/local/lib") 

### Options ###

option(BUILD_TEST  "Build cyan_fileio tests" ON)
option(BUILD_TOOLS "Build cyan_fileio tools" ON)

###Search for libpng

find_package(cyan REQUIRED)
find_package(ImageMagick COMPONENTS MagickCore) 

SET(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -fopenmp -DMAGICKCORE_HDRI_ENABLE=0 -DMAGICKCORE_QUANTUM_DEPTH=16")

### Config File

configure_file ( "${PROJECT_SOURCE_DIR}/fileio.h.in" 
			     "${PROJECT_SOURCE_DIR}/include/cyan/fileio/fileio.h" )

### Set include directories 
        
include_directories( "${CMAKE_CURRENT_SOURCE_DIR}/include/"
	                 "${CMAKE_CURRENT_BINARY_DIR}" 
                     "${ImageMagick_INCLUDE_DIRS}"
                     "${ImageMagick_MagickCore_INCLUDE_DIRS}"
                     ) 

### File lists

file( GLOB src  "src/*.c" )
file( GLOB hdr  "include/cyan/fileio/*.h"  )

### Targets

add_library( "cyan_fileio" SHARED ${src} ) 

set_target_properties(cyan_fileio PROPERTIES VERSION ${cyan_fileio_VERSION}
                                    SOVERSION ${cyan_fileio_VERSION_MAJOR})

### Linking

target_link_libraries( "cyan_fileio" 
                     "${CYAN_LIBRARY}"
                     "${ImageMagick_LIBRARIES}" )


### Cmake file

configure_file(cyan_fileioConfig.cmake.in "${PROJECT_BINARY_DIR}/cyan_fileioConfig.cmake" @ONLY)

install ( FILES "${PROJECT_BINARY_DIR}/cyan_fileioConfig.cmake" 
      DESTINATION "${INSTALL_LIB_PATH}/cyan_fileio" COMPONENT dev )  

### Install 

install( TARGETS "cyan_fileio"
	    RUNTIME DESTINATION ${INSTALL_BIN_PATH}  COMPONENT main
	    LIBRARY DESTINATION ${INSTALL_LIB_PATH}  COMPONENT main
	    ARCHIVE DESTINATION ${INSTALL_AR_PATH}   COMPONENT main ) 

install( FILES ${hdr}
	    DESTINATION ${INSTALL_HEADERS_PATH}/cyan/fileio/${name} 
	    COMPONENT main )

# Regression tests

if (BUILD_TEST)
    enable_testing()
    add_subdirectory(test)
endif()

if (BUILD_TOOLS)
    add_subdirectory(tools)
endif() 

# Cpack specifics

set (CPACK_PACKAGE_CONTACT "seb@homedruon.com")
include(CPack)

### Pretty Display :

MESSAGE(STATUS "*********************************************************")
MESSAGE(STATUS "")
MESSAGE(STATUS "Build type:        " ${CMAKE_BUILD_TYPE})
MESSAGE(STATUS "")
MESSAGE(STATUS "BUILD_TOOLS:       " ${BUILD_TOOLS})
MESSAGE(STATUS "BUILD_TEST:        " ${BUILD_TEST})
MESSAGE(STATUS "")
MESSAGE(STATUS "*********************************************************")
