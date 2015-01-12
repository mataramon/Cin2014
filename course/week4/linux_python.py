import sys
from ctypes import *
import ctypes
import os
# Ctypes allow interface c function
# if the dll is charged from a c++ code then
# you must provide c linkage

def main():
    folder = os.path.dirname(os.path.realpath(__file__))
    library = os.path.join(folder, "padts_library.so")
    #update the path must be the absolute path on linux
    library = cdll.LoadLibrary(library)
    print (library.myRealC)
    z = library.myRealC()
    print (z)
    # Passing the arguments to the function
    message = create_string_buffer("u_u alles ist gut here")
    library.Message(len(message), message)
   
    
if __name__ == '__main__':
    ret = main()
    if ret:
        sys.exit(0)
        
    sys.exit(1)
