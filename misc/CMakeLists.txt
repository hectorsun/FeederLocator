find_package(Qt5Widgets)
project(misc)

add_definitions(-DMISCAPI_EXPORTS)
add_definitions(-DBOOST_ALL_DYN_LINK)

# copy all header file in "${CMAKE_CURRENT_SOURCE_DIR}/include/"
#  into "${CMAKE_BINARY_DIR}/include/misc"
file(GLOB MISC_INC 
  RELATIVE "${CMAKE_CURRENT_SOURCE_DIR}/include/"
  "${CMAKE_CURRENT_SOURCE_DIR}/include/*.h")
foreach(MISC_INC_FILE ${MISC_INC})
  file(COPY
    "${CMAKE_CURRENT_SOURCE_DIR}/include/${MISC_INC_FILE}"
    DESTINATION "${INC_DIR}/misc/")
endforeach()

# add include directories: "${CMAKE_CURRENT_SOURCE_DIR}/include"
include_directories("${INC_DIR}")
include_directories("${CMAKE_CURRENT_SOURCE_DIR}/../GUI/src")
include_directories("${CMAKE_CURRENT_SOURCE_DIR}/src/")
include_directories(${Boost_INCLUDE_DIRS})
add_library(misc SHARED src/CDataSet.cpp
	src/CSuperTerminal.cpp)



target_link_libraries(misc Qt5::Widgets ${Boost_LIBRARIES})
#message("${OpenCV_LIBS}")
message("${Boost_LIBRARIES}")
if (WIN32)
  install(TARGETS misc DESTINATION "${CMAKE_INSTALL_PREFIX}")
else(not WIN32)
  install(TARGETS misc DESTINATION "${CMAKE_INSTALL_PREFIX}/lib")
endif()
