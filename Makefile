CPP = g++ -std=c++20 -Wall -Wextra -Werror -Wfatal-errors -pedantic -Isrc

dijkstras.o : src/dijkstras.h src/dijkstras.cpp
	$(CPP) -c src/dijkstras.cpp -o dijkstras.o

ladder.o : src/ladder.h src/ladder.cpp
	$(CPP) -c src/ladder.cpp -o ladder.o

main : ladder.o src/ladder_main.cpp dijkstras.o src/dijkstras_main.cpp
	$(CPP) src/ladder_main.cpp ladder.o -o ladder_main
	$(CPP) src/dijkstras_main.cpp dijkstras.o -o dijkstras_main

clean:
	rm *.o ladder_main dijkstras_main
