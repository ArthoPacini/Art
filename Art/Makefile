CC=g++-9
CCWIN=g++
CFLAGS=-std=c++17 -Wall -O3 -pthread

all:
	cd ./examples && $(CC) vecTest.cpp -o ../binaries/vecTest $(CFLAGS)
	cd ./examples && $(CC) helloworld.cpp -o ../binaries/helloworld $(CFLAGS)
	cd ./examples && $(CC) renderFunction.cpp -o ../binaries/renderFunction $(CFLAGS)
	cd ./examples && $(CC) randomCircles.cpp -o ../binaries/randomCircles $(CFLAGS)
	cd ./examples && $(CC) randomTriangles.cpp -o ../binaries/randomTriangles $(CFLAGS)
	cd ./examples && $(CC) randomMultiLine.cpp -o ../binaries/randomMultiLine $(CFLAGS)
	cd ./examples && $(CC) randomPolygons.cpp -o ../binaries/randomPolygons $(CFLAGS)
	cd ./examples && $(CC) randomRectangles.cpp -o ../binaries/randomRectangles $(CFLAGS)
	cd ./examples && $(CC) randomDude.cpp -o ../binaries/randomDude $(CFLAGS)
	#now testing everything... except for renderFunction
	cd ./binaries && ./vecTest
	cd ./binaries && ./helloworld
	cd ./binaries && ./randomCircles
	cd ./binaries && ./randomTriangles
	cd ./binaries && ./randomMultiLine
	cd ./binaries && ./randomPolygons
	cd ./binaries && ./randomRectangles
	cd ./binaries && ./randomDude