battleship: battleplace.o battlebot.o main.o
	g++ battleplace.o battlebot.o main.o -o battleship
battleplace.o: battleplace.cpp battleplace.h
	g++ -c battleplace.cpp
battlebot.o: battlebot.cpp battlebot.h
	g++ -c battlebot.cpp
main.o: main.cpp 
	g++ -c main.cpp
clean:
	rm *.o
