#!/usr/bin/env python
import sys

from ctypes import *
# Ctypes allow interface c function
# if the dll is charged from a c++ code then
# you must provide c linkage

def main():
    library = cdll.LoadLibrary("library.dll")
    print (library.get_item)
    z = library.get_item()
    print (z)
    
    
if __name__ == '__main__':
    ret = main()
    if ret:
        sys.exit(0)
        
    sys.exit(1)