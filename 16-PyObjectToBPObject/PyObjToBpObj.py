#!/usr/bin/env python
import sys
from PyObjectToBpObject import *

a = RetNewPyStr()
b = RetBpStr()
c = RetBpBorrowObj()
d = {1:2,3:4}
print sys.getrefcount(a)
print sys.getrefcount(b)
print sys.getrefcount(c)

print sys.getrefcount(d)