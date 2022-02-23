all : bld

bld :
	g++ -std=c++11 pepin.cpp -o 3Dprog -lGL -lGLU -lglut

clean :
	rm 3Dprog

br :
	g++ -std=c++11 pepin.cpp -o 3Dprog -lGL -lGLU -lglut
	./3Dprog

r :
	./3Dprog
