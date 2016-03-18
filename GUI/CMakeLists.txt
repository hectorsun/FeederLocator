find_package(Qt5Widgets)


set(CMAKE_AUTOMOC ON)
set(CMAKE_INCLUDE_CURRENT_DIR ON)


# copy all header file in "${CMAKE_CURRENT_SOURCE_DIR}/include/"
#  into "${CMAKE_BINARY_DIR}/include/GUI"
file(GLOB CAM_INC 
  RELATIVE "${CMAKE_CURRENT_SOURCE_DIR}/include/"
  "${CMAKE_CURRENT_SOURCE_DIR}/include/*.h")
foreach(CAM_INC_FILE ${CAM_INC})
  file(COPY
    "${CMAKE_CURRENT_SOURCE_DIR}/include/${CAM_INC_FILE}"
    DESTINATION "${INC_DIR}/GUI/")
endforeach()

# add include directories: "${CMAKE_CURRENT_SOURCE_DIR}/include"
include_directories("${INC_DIR}")
include_directories("${CMAKE_CURRENT_SOURCE_DIR}/src/")

qt5_add_resources(RESOURCE_ADDED "${CMAKE_CURRENT_SOURCE_DIR}/src/GUI.qrc")

add_executable(FeederLocator
  "${CMAKE_CURRENT_SOURCE_DIR}/src/CMainWindow.cpp"
  "${CMAKE_CURRENT_SOURCE_DIR}/src/CPaintWidget.cpp"
  "${CMAKE_CURRENT_SOURCE_DIR}/src/main.cpp"
  "${CMAKE_CURRENT_SOURCE_DIR}/src/CThread.cpp"
  "${RESOURCE_ADDED}")

target_link_libraries(FeederLocator Qt5::Widgets camera)

if(WIN32)
  install(TARGETS FeederLocator DESTINATION "${CMAKE_INSTALL_PREFIX}")
else()
  install(TARGETS FeederLocator DESTINATION "${CMAKE_INSTALL_PREFIX}/bin")
endif()
