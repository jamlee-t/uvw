#----------------------------------------------------------------
# Generated CMake target import file for configuration "Debug".
#----------------------------------------------------------------

# Commands may need to know the format version.
set(CMAKE_IMPORT_FILE_VERSION 1)

# Import target "uvw::uvw" for configuration "Debug"
set_property(TARGET uvw::uvw APPEND PROPERTY IMPORTED_CONFIGURATIONS DEBUG)
set_target_properties(uvw::uvw PROPERTIES
  IMPORTED_LINK_INTERFACE_LANGUAGES_DEBUG "CXX"
  IMPORTED_LOCATION_DEBUG "${_IMPORT_PREFIX}/lib/libuvw.a"
  )

list(APPEND _IMPORT_CHECK_TARGETS uvw::uvw )
list(APPEND _IMPORT_CHECK_FILES_FOR_uvw::uvw "${_IMPORT_PREFIX}/lib/libuvw.a" )

# Import target "uvw::uv_a" for configuration "Debug"
set_property(TARGET uvw::uv_a APPEND PROPERTY IMPORTED_CONFIGURATIONS DEBUG)
set_target_properties(uvw::uv_a PROPERTIES
  IMPORTED_LINK_INTERFACE_LANGUAGES_DEBUG "C"
  IMPORTED_LOCATION_DEBUG "${_IMPORT_PREFIX}/lib/uvw/libuv_a.a"
  )

list(APPEND _IMPORT_CHECK_TARGETS uvw::uv_a )
list(APPEND _IMPORT_CHECK_FILES_FOR_uvw::uv_a "${_IMPORT_PREFIX}/lib/uvw/libuv_a.a" )

# Commands beyond this point should not need to know the version.
set(CMAKE_IMPORT_FILE_VERSION)
