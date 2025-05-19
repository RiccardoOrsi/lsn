CC = g++
CFLAGS = -Wall -O3 --std=c++11

run: main.exe
	./main.exe

main.exe : main.o random.o librerie.o
	$(CC) random.o librerie.o main.o -o main.exe

main.o : main.cpp
	$(CC) -c main.cpp -o main.o $(CFLAGS)

random.o : ../../rnd_gen/random.cpp ../../rnd_gen/random.h
	$(CC) -c ../../rnd_gen/random.cpp -o random.o $(CFLAGS)

librerie.o : ../../librerie/librerie.cpp ../../librerie/librerie.h
	$(CC) -c ../../librerie/librerie.cpp -o librerie.o $(CFLAGS)


clean :
	rm *.o main.exe seed.out
clean_results :
	rm *.out
clean-all:
	clean clean_results
