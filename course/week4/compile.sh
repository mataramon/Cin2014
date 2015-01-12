echo "Creating object code"
# -Wall = warning all
# fPIC  = preserve the flags used
# -c    = compile and generate the assembly but not run the linker
g++ -Wall -fPIC -c linux_library.cpp;
echo "Creating the library"
# shared  = shared library
# -Wl     = Warning linker
# -soname = Library so name
# -o      = outputfile 
g++ -shared -Wl,-soname,padts_library.so.1 -o padts_library.so linux_library.o
echo "Running example"
python linux_python.py
