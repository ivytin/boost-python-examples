#include <boost/python.hpp>

// Legacy API.
class A
{
public:
	A() : b_(false)   {}
	A(bool b) : b_(b) {}
	bool is_B() const { return b_; } // true if conversion to B will succeed
private:
	bool b_;
};

class B: public A
{
public:
	B() : A()            {}
	B(const A& a) : A(a) {}
};

/// @brief Factory functions that return an A type with is_B of false.
A make_A() { return A(false); }

/// @brief Factory functions that return an A type with is_B of true.
A make_B() { return A(true);  }

/// @brief Custom converter that converts A to either an A or B Python object.
struct class_A_cref_wrapper
		: boost::python::to_python_converter<A, class_A_cref_wrapper>
{
	// Make and hold instances by value.
	typedef boost::python::objects::make_instance<A,
			boost::python::objects::value_holder<A>
	> instance_maker;

	static PyObject* convert(const A& a)
	{
		namespace python = boost::python;
		return a.is_B()
		       ? python::incref(python::object(B(a)).ptr()) // Create B.
		       : instance_maker::execute(boost::ref(a));    // Create A.
	}
};

BOOST_PYTHON_MODULE(to_python_converter)
{
	namespace python = boost::python;

	// Expose A and B classes.  Use boost::noncopyable to suppress to-Python
	// and from-Python converter regristration for class A.
	python::class_<A, boost::noncopyable>("A");
	python::class_<B, python::bases<A> >("B");

	// Register a custom converter for A.
	class_A_cref_wrapper();

	// Expose factory functions that always return an A type.  This will
	// cause to_python converters to be invoked when invoked from Python.
	python::def("make_A", &make_A);
	python::def("make_B", &make_B);
}