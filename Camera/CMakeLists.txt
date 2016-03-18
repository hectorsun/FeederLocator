
project(camera)

set(CameraSimulate CACHE BOOL "Read image from disk")
add_definitions(-DCAMAPI_EXPORTS)


if(CameraSimulate)
	message(STATUS "CameraSimulate")
	set(PIC_DIR "${CMAKE_CURRENT_SOURCE_DIR}/figure/1.bmp")
	find_package(OpenCV REQUIRED)
	include_directories(${OpenCV_INCLUDE_DIRS})
	add_definitions(-DPicPath="${PIC_DIR}")
	add_library(camera SHARED CCameraSimu.cpp)
	target_link_libraries(camera ${OpenCV_LIBS})
	#file(COPY ${PIC_DIR} DESTINATION "${BIN_DIR}")

	if (WIN32)
	  install(PROGRAMS "${CMAKE_CURRENT_SOURCE_DIR}/figure/1.bmp" DESTINATION "${CMAKE_INSTALL_PREFIX}")
	else()
	  #install(PROGRAMS )
	endif()
	
	  
	

else(not CameraSimulate)
	add_library(camera SHARED CCamera.cpp)
endif()



if (WIN32)
  install(TARGETS camera DESTINATION "${CMAKE_INSTALL_PREFIX}")
else()
  install(TARGETS camera DESTINATION "lib")
endif()