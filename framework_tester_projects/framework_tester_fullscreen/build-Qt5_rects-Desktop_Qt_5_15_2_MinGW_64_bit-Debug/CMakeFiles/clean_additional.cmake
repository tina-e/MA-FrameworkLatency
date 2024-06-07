# Additional clean files
cmake_minimum_required(VERSION 3.16)

if("${CONFIG}" STREQUAL "" OR "${CONFIG}" STREQUAL "Debug")
  file(REMOVE_RECURSE
  "CMakeFiles\\Qt5_rects_autogen.dir\\AutogenUsed.txt"
  "CMakeFiles\\Qt5_rects_autogen.dir\\ParseCache.txt"
  "Qt5_rects_autogen"
  )
endif()
