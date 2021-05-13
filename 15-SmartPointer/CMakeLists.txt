
PYTHON_ADD_MODULE(smart_pointer smart_pointer.cpp)
FILE(COPY smart_pointer.py DESTINATION .)
ADD_TEST(NAME 15-SmartPointer COMMAND ${PYTHON_EXECUTABLE} smart_pointer.py)
