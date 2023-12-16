INC=-I../rpi-rgb-led-matrix/include

all: eyes

eyes: eyes.o
	g++ -o eyes eyes.o

eyes.o: eyes.cpp
	g++ $(INC) -c eyes.cpp
