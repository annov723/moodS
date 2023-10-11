all: moodS

moodS: main.o mood.o
		g++ main.o mood.o -o moodS

main.o: main.cpp
		g++ -c main.cpp

mood.o: mood.cpp
		g++ -c mood.cpp

clean:
		rm -rf *o moodS