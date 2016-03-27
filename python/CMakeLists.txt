project(python)

set(BUILD_python TRUE CACHE BOOL "build python wrapper")

list(APPEND CMAKE_MODULE_PATH ${PROJECT_SOURCE_DIR}/cmake/Modules)
#message("${CMAKE_MODULE_PATH}")

# find necessary packages
include("cmake/Dependencies.cmake")


if (NOT HAVE_PYTHON)
  message(STATUS "have not python")
  return()
endif()

include_directories("${INC_DIR}")

include_directories(${PYTHON_INCLUDE_DIRS} ${NUMPY_INCLUDE_DIR} ${Boost_INCLUDE_DIRS})
file(GLOB_RECURSE python_srcs ${CMAKE_SOURCE_DIR}/python/FeederLocator/*.cpp)


add_library(pyfeeder SHARED ${python_srcs})
target_link_libraries(pyfeeder imgProc ${PYTHON_LIBRARIES} ${Boost_LIBRARIES})
#set_target_properties(pyfeeder PROPERTIES PREFIX "" OUTPUT_NAME "_feeder")
set_target_properties(pyfeeder PROPERTIES PREFIX ""
  LIBRARY_OUTPUT_DIRECTORY "${CMAKE_SOURCE_DIR}/python/FeederLocator/"
  OUTPUT_NAME "_feeder")
