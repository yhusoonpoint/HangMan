HangMan: Main.o Getline.o Person.o Manager.o Gamer.o ReadWords.o Random.o IOFile.o
	g++ Main.o Getline.o Person.o Manager.o Gamer.o ReadWords.o Random.o IOFile.o -o HangMan
Main.o: main.cpp
	g++ -c main.cpp
Getline.o: Getline.cpp Getline.h
	g++ -c Getline.cpp
Person.o: Person.cpp Person.h
	g++ -c Person.cpp
Manager.o: Manager.cpp Manager.h
	g++ -c Manager.cpp
Gamer.o: Gamer.cpp Gamer.h
	g++ -c Gamer.cpp
ReadWords.o: ReadWords.cpp ReadWords.h
	g++ -c ReadWords.cpp
Random.o: Random.cpp Random.h
	g++ -c Random.cpp
IOFile.o: IOFile.cpp IOFile.h
	g++ -c IOFile.cpp

clean:
	del *.o HangMan
