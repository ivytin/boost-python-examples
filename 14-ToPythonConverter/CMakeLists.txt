
PYTHON_ADD_MODULE(to_python_converter to_python_converter.cpp)
FILE(COPY to_python_converter.py DESTINATION .)
ADD_TEST(NAME 14-ToPythonConverter COMMAND ${PYTHON_EXECUTABLE} to_python_converter.py)
