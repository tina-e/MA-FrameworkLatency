# Additional clean files
cmake_minimum_required(VERSION 3.16)

if("${CONFIG}" STREQUAL "" OR "${CONFIG}" STREQUAL "Debug")
  file(REMOVE_RECURSE
  "CMakeFiles\\appQt6_quick_default_autogen.dir\\AutogenUsed.txt"
  "CMakeFiles\\appQt6_quick_default_autogen.dir\\ParseCache.txt"
  "appQt6_quick_default_autogen"
  )
endif()
