SRCS = main.cpp SoundEffect.cpp soundhandler.cpp
#DEPS = SoundEffect.h soundhanlder.h
OBJS = $(SRCS:.cpp=.o)
MAIN = test.exe
## Preprocesor flags
CPPFLAGS = -I"include"
LDFLAGS = -L"/usr/lib" "-pthread" "bin/linux-gcc-64/libIrrKlang.so"
## Complier flags
CFLAGS = -std=c++11 -Wall
RM = rm -rf

all: $(MAIN)
	@echo "Succesfully created $(MAIN)"

$(MAIN): $(OBJS) 
	@echo "Building target: $@"
	@echo "Invoking GCC G++ Linker"
	$(CXX) $(OBJS) -o $@ $(CPPFLAGS) $(LDFLAGS)
	@echo "Finished building target $@"
	@echo " "

## Default naming, same as source.
%.o: %.cpp $(DEPS)
	@echo "Building file: $<"
	@echo "Invoking GCC G++ Compiler"
	$(CXX) $(CFLAGS) -c  $< $(CPPFLAGS) 
	@echo "Finished building $<"
	@echo " "

clean:
	$(RM) $(OBJS) $(MAIN) *.gch *~

# Default: CXX = g++
# RM $(OBJS) $(MAIN)
