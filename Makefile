CPP = g++ -std=c++20 -Wall -Wextra -Werror -Wfatal-errors -pedantic -Isrc

dijkstras.o : src/dijkstras.h src/dijkstras.cpp
	$(CPP) -c src/dijkstras.cpp -o dijkstras.o

ladder.o : src/ladder.h src/ladder.cpp
	$(CPP) -c src/ladder.cpp -o ladder.o

clean:
	rm *.o
