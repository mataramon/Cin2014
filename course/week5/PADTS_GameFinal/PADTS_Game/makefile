OUTDIR = build
CFLAGS = -std=c++11 -W
SRCS = main.cpp Bala.cpp Enemy.cpp Objeto.cpp SDL_Fus.cpp SoundEffect.cpp soundhandler.cpp
OBJS = $(patsubst %.cpp,  $(OUTDIR)/%.o, $(SRCS))
MAIN = game.exe
## Preprocesor flags
CPPFLAGS = -I"include" "/usr/include"
LDFLAGS = -L"/usr/lib" "bin/linux-gcc-64/libIrrKlang.so" "-pthread" -l"SDL2"
## Complier flags
RM = rm -rf

all: $(MAIN)
	@echo "Succesfully created $(MAIN)"


$(MAIN): build $(OBJS) 
	@echo "Building target: $@"
	@echo "Invoking GCC G++ Linker"
#	$(CXX) $(OBJS) -o $@ $(CPPFLAGS) $(LDFLAGS)
	$(CXX) $(OBJS) -o $@ $(LDFLAGS)
	@echo "Finished building target $@"
	@echo " "

## Default naming, same as source.
$(OBJS): $(OUTDIR)/%.o: %.cpp
	@echo "Bulding file $<"
	@echo "Invoking GCC G++ Compiler"
	$(CXX) $(CFLAGS) -c  $< -o $@ $(CPPFLAGS)
	@echo "Finished building: $<" 
	@echo " "

.PHONY: clean sdl
clean:
	$(RM) $(OUTDIR) $(MAIN) ikpMP3.so *~

build: 
	@echo " "
	@echo "Intalling SDL ... "
	@sudo apt-get install libsdl2-dev libsdl1.2-dev libsdl-image1.2-dev libsdl-mixer1.2-dev libsdl-ttf2.0-dev
	@echo " "
	@echo "Creating output directory ... "
	mkdir -p $(OUTDIR)
	cp bin/linux-gcc-64/ikpMP3.so .
	@echo " "

# Default: CXX = g++
# RM $(OBJS) $(MAIN)
