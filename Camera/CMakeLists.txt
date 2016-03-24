
project(Camera)



add_definitions(-DCAMAPI_EXPORTS)


# copy all header file in "${CMAKE_CURRENT_SOURCE_DIR}/include/"
#  into "${CMAKE_BINARY_DIR}/include/Camera"
file(GLOB CAM_INC 
  RELATIVE "${CMAKE_CURRENT_SOURCE_DIR}/include/"
  "${CMAKE_CURRENT_SOURCE_DIR}/include/*.h")
foreach(CAM_INC_FILE ${CAM_INC})
  file(COPY
    "${CMAKE_CURRENT_SOURCE_DIR}/include/${CAM_INC_FILE}"
    DESTINATION "${INC_DIR}/Camera")
endforeach()

# add include directories: "${CMAKE_BINARY_DIR}/include/" 
include_directories(${INC_DIR})


include_directories(${OpenCV_INCLUDE_DIRS})
  
# choice camera mode
set(CameraSimulate CACHE BOOL "Read image from disk")
if(CameraSimulate)
  message(STATUS "CameraSimulate")

  
  set(PIC_DIR "${CMAKE_CURRENT_SOURCE_DIR}/figure/1.bmp")
  add_definitions(-DPicPath="${PIC_DIR}")
  
  add_library(Camera SHARED src/CCameraSimu.cpp)
  
else(not CameraSimulate)
  set(Daheng_DIR CACHE PATH "Daheng sdk dir")
  set(Daheng_LIB_DIR "${Daheng_DIR}/lib/x86/")
  set(Daheng_LIB "${Daheng_LIB_DIR}/GxIAPI.lib")

  include_directories("${Daheng_DIR}/inc")
  add_library(Camera SHARED src/CCamera.cpp)
  target_link_libraries(Camera ${Daheng_LIB})
endif()

target_link_libraries(Camera ${OpenCV_LIBS})

if (WIN32)
  install(TARGETS Camera DESTINATION "${CMAKE_INSTALL_PREFIX}")
else()
  install(TARGETS Camera DESTINATION "${CMAKE_INSTALL_PREFIX}/lib")
endif()
