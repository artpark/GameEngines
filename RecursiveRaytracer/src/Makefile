all : rraytracer
	

rraytracer : rraytracer.o
	g++ -Wall -Wextra -Wpedantic -Wshadow -o rraytracer rraytracer.o

rraytracer.o : rraytracer.cpp
	g++ -Wall -Wextra -Wpedantic -Wshadow -c rraytracer.cpp

clean : 
	rm -f rraytracer.o

spotless : clean
	rm -f rraytracer output.ppm