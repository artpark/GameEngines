all : main
	

main : main.o
	g++ -Wall -Wextra -Wpedantic -Wshadow -o main main.o

main.o : main.cpp
	g++ -Wall -Wextra -Wpedantic -Wshadow -c main.cpp

clean : 
	rm -f main.o

spotless : clean
	rm -f main output.ppm