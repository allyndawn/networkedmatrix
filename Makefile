all: eyes

eyes: eyes.o
	g++ -o eyes eyes.o

eyes.o: eyes.cpp
	g++ -c eyes.cpp
