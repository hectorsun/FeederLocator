
project(misc)

add_definitions(-DMISCAPI_EXPORTS)

# copy all header file in "${CMAKE_CURRENT_SOURCE_DIR}/include/"
#  into "${CMAKE_BINARY_DIR}/include/misc"
file(GLOB CAM_INC 
  RELATIVE "${CMAKE_CURRENT_SOURCE_DIR}/include/"
  "${CMAKE_CURRENT_SOURCE_DIR}/include/*.h")
foreach(CAM_INC_FILE ${CAM_INC})
  file(COPY
    "${CMAKE_CURRENT_SOURCE_DIR}/include/${CAM_INC_FILE}"
    DESTINATION "${INC_DIR}/misc/")
endforeach()

# add include directories: "${CMAKE_CURRENT_SOURCE_DIR}/include"
include_directories("${INC_DIR}")

find_package(OpenCV REQUIRED)
find_package(Boost REQUIRED)
include_directories(${OpenCV_INCLUDE_DIRS} ${Boost_INCLUDE_DIRS})
add_library(misc SHARED src/CDataSet.cpp
  src/imgProc.cpp
  src/baseLocate.cpp
  src/chipLocate.cpp)
target_link_libraries(misc ${OpenCV_LIBS} ${Boost_LIBRARIES})
#message("${OpenCV_LIBS}")

if (WIN32)
  install(TARGETS misc DESTINATION "${CMAKE_INSTALL_PREFIX}")
else(not WIN32)
  install(TARGETS misc DESTINATION "${CMAKE_INSTALL_PREFIX}/lib")
endif()
