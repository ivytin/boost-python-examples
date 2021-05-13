#include <memory>
#include <boost/python.hpp>
#include <memory>

struct A {
  virtual int f() { return intVal; }

private:
  int intVal = 2;
};

std::shared_ptr<A> New() {
  return std::make_shared<A>();
}

int Ok(const std::shared_ptr<A> &a) {
  return a->f();
}

int Fail(std::shared_ptr<A> &a) {
  return a->f();
}

A TestWithoutToPythonConvert() {
  return A();
}

struct A_Wrapper : A {
  A_Wrapper(PyObject *self_) : self(self_) {}
  int f() override {
    return boost::python::call_method<int>(self, "f");
  }
  int default_f() {
    return A::f();
  }
  PyObject *self;
};


BOOST_PYTHON_MODULE(smart_pointer) {
  // since no ctor for init A_Wrapper from A, it should be noncopyable
  // and TestWithoutToPythonConvert will fail to return a Python A cls instance
  boost::python::class_<A, A_Wrapper, boost::noncopyable>("A")
      .def("f", &A::f, &A_Wrapper::default_f);

  boost::python::def("New", &New);
  boost::python::def("Ok", &Ok);
  boost::python::def("Fail", &Fail);
  boost::python::def("TestWithoutToPythonConvert", &TestWithoutToPythonConvert);

  boost::python::register_ptr_to_python<std::shared_ptr<A> >();
}