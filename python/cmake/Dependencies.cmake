
# found python 2.7
if(BUILD_python)
  find_package(PythonInterp 2.7)
  find_package(PythonLibs 2.7)
  find_package(Numpy 1.7.1)
  find_package(Boost 1.46 COMPONENTS python)
  if (PYTHONLIBS_FOUND AND NUMPY_FOUND AND Boost_PYTHON_FOUND)
    set(HAVE_PYTHON TRUE)
    
  endif()
endif()