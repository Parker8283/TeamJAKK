# Find IrrKlang header and library (tested with version 1.1.3c)

# This module defines the following uncached variables:
#  IrrKlang_FOUND, if false, do not try to use IrrKlang
#  IrrKlang_INCLUDE_DIRS, where to find irrKlang.h.
#  IrrKlang_LIBRARIES, the libraries to link against to use IrrKlang
#  IrrKlang_LIBRARY_DIRS, the directory where the IrrKlang library is found.

SET(IrrKlang_FOUND OFF)

FIND_PATH(
  IrrKlang_INCLUDE_DIR
		irrKlang.h 
		/usr/local/include 
		/usr/include
		${CMAKE_SOURCE_DIR}/opengllib/Include
)

IF(IrrKlang_INCLUDE_DIR)
  find_library(IrrKlang_LIBRARY
    NAMES IrrKlang
    PATHS /usr/local/lib /usr/lib ${CMAKE_SOURCE_DIR}/opengllib/Lib
	)
  if(IrrKlang_LIBRARY)
    get_filename_component(IrrKlang_LIBRARY_DIRS ${IrrKlang_LIBRARY} PATH)
    # Set uncached variables as per standard.
    set(IrrKlang_FOUND ON)
    set(IrrKlang_INCLUDE_DIRS ${IrrKlang_INCLUDE_DIR})
    set(IrrKlang_LIBRARIES ${IrrKlang_LIBRARY})
  endif(IrrKlang_LIBRARY)
endif(IrrKlang_INCLUDE_DIR)
	    
if(IrrKlang_FOUND)
  if(NOT IrrKlang_FIND_QUIETLY)
    message(STATUS "FindIrrKlang: Found both IrrKlang headers and library")
  endif(NOT IrrKlang_FIND_QUIETLY)
else(IrrKlang_FOUND)
  if(IrrKlang_FIND_REQUIRED)
    message(FATAL_ERROR "FindIrrKlang: Could not find IrrKlang headers or library")
  endif(IrrKlang_FIND_REQUIRED)
endif(IrrKlang_FOUND)

MARK_AS_ADVANCED(
  IrrKlang_INCLUDE_DIR
  IrrKlang_LIBRARY
)