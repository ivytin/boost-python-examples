#include <boost/python.hpp>

PyObject* RetNewPyStr() {
  return PyString_FromString("hello");
}

PyObject* RetDict() {
  PyObject* newDict = PyDict_New();
  PyObject* keyObj = PyInt_FromLong(1);
  PyObject* valObj = RetNewPyStr();
  int ret = PyDict_SetItem(newDict, keyObj, valObj);
  assert(ret == 0);
  Py_DecRef(keyObj);
  Py_DecRef(valObj);
  return newDict;
}

boost::python::object RetBpObj() {
  PyObject* pyStr = RetNewPyStr();
  return boost::python::object(boost::python::handle<>(pyStr));
}

boost::python::object RetBpBorrowObj() {
  PyObject* dictObj = RetDict();
  PyObject* keyObj = PyInt_FromLong(1);
  PyObject* borrowedObj = PyDict_GetItem(dictObj, keyObj);
  auto handler = boost::python::handle<>(boost::python::borrowed(borrowedObj));
  Py_DecRef(keyObj);
  Py_DecRef(dictObj);
  return boost::python::object(handler);
}


BOOST_PYTHON_MODULE(PyObjectToBpObject) {

  boost::python::def("RetNewPyStr", &RetNewPyStr);
  boost::python::def("RetBpStr", &RetBpObj);
  boost::python::def("RetBpBorrowObj", &RetBpBorrowObj);
}