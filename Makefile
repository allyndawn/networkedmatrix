RGB_LIB_DISTRIBUTION=../rpi-rgb-led-matrix
RGB_INCDIR=$(RGB_LIB_DISTRIBUTION)/include
RGB_LIBDIR=$(RGB_LIB_DISTRIBUTION)/lib
RGB_LIBRARY_NAME=rgbmatrix
RGB_LIBRARY=$(RGB_LIBDIR)/lib$(RGB_LIBRARY_NAME).a
LDFLAGS+=-L$(RGB_LIBDIR) -l$(RGB_LIBRARY_NAME) -lrt -lm -lpthread

all: eyes

eyes: eyes.o renderer.o static-eyes-renderer.o $(RGB_LIBRARY)
	g++ -o eyes eyes.o renderer.o static-eyes-renderer.o $(LDFLAGS)

eyes.o: eyes.cpp
	g++ -I$(RGB_INCDIR) -c eyes.cpp

renderer.o: renderers/renderer.cpp
	g++ -I$(RGB_INCDIR) -c renderers/renderer.cpp

static-eyes-renderer.o: renderers/static-eyes-renderer.cpp
	g++ -I$(RGB_INCDIR) -c renderers/static-eyes-renderer.cpp

