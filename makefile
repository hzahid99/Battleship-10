Battleship: main.o Board.o Player.o Game.o Ship.o AI.o
	g++ -std=c++11 -g -Wall main.o Board.o Player.o Game.o Ship.o AI.o -o Battleship
main.o: 
	g++ -std=c++11 -g -Wall -c main.cpp
Board.o: 
	g++ -std=c++11 -g -Wall -c Board.cpp
Player.o:
	g++ -std=c++11 -g -Wall -c Player.cpp
Game.o: 
	g++ -std=c++11 -g -Wall -c Game.cpp
Ship.o:
	g++ -std=c++11 -g -Wall -c Ship.cpp
AI.o:
	g++ -std=c++11 -g -Wall -c AI.cpp
clean:
	rm *.o Battleship
