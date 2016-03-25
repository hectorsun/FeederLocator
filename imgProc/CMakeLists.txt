project(imgProc)

add_definitions(-DIMGPROCAPI_EXPORTS)

# copy all header file in "${CMAKE_CURRENT_SOURCE_DIR}/include/"
#  into "${CMAKE_BINARY_DIR}/include/misc"
file(GLOB IMG_INC 
  RELATIVE "${CMAKE_CURRENT_SOURCE_DIR}/include/"
  "${CMAKE_CURRENT_SOURCE_DIR}/include/*.h")
foreach(IMG_INC_FILE ${IMG_INC})
  file(COPY
    "${CMAKE_CURRENT_SOURCE_DIR}/include/${IMG_INC_FILE}"
    DESTINATION "${INC_DIR}/imgProc/")
endforeach()

# add include directories: "${CMAKE_CURRENT_SOURCE_DIR}/include"
include_directories("${INC_DIR}")


include_directories(${OpenCV_INCLUDE_DIRS} ${Boost_INCLUDE_DIRS})
add_library(imgProc SHARED 
  src/imgProc.cpp
  src/baseLocate.cpp
  src/chipLocate.cpp)
target_link_libraries(imgProc ${OpenCV_LIBS} ${Boost_LIBRARIES})

if (WIN32)
  install(TARGETS imgProc DESTINATION "${CMAKE_INSTALL_PREFIX}")
else(not WIN32)
  install(TARGETS imgProc DESTINATION "${CMAKE_INSTALL_PREFIX}/lib")
endif()
