# Additional clean files
cmake_minimum_required(VERSION 3.16)

if("${CONFIG}" STREQUAL "" OR "${CONFIG}" STREQUAL "Release")
  file(REMOVE_RECURSE
  "CMakeFiles\\Qt6_rects_autogen.dir\\AutogenUsed.txt"
  "CMakeFiles\\Qt6_rects_autogen.dir\\ParseCache.txt"
  "Qt6_rects_autogen"
  )
endif()
