#include <Python.h>

// Produce deprecation warnings (needs to come before arrayobject.h inclusion).
#define NPY_NO_DEPRECATED_API NPY_1_7_API_VERSION

#include <boost/make_shared.hpp>
#include <boost/python.hpp>
#include <boost/python/raw_function.hpp>
#include <boost/python/suite/indexing/vector_indexing_suite.hpp>
#include <numpy/arrayobject.h>

#include <imgProc/imgProc.h>

namespace bp = boost::python;


namespace feeder{
  BOOST_PYTHON_MODULE(_feeder){

    bp::class_<imgPoint>("imgPoint")
      .def(bp::init<bp::optional<int, int> >())
      .def_readonly("x", &imgPoint::x)
      .def_readonly("y", &imgPoint::y)
      ;




  }
};
