all: testplayer

testplayer: testplayer.o CPlayer.o
	g++ CPlayer.o testplayer.o -o testplayer

testplayer.o: testplayer.cpp
	g++ -c testplayer.cpp

CPlayer.o: CPlayer.cpp
	gcc -c CPlayer.cpp
