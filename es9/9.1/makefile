CC = g++
CFLAGS = -Wall -O3 --std=c++11
RND = ../../rnd_gen/

main.exe : main.o random.o functions.o
	$(CC) random.o functions.o main.o -o main.exe
main.o : main.cpp functions.h
	$(CC) -c main.cpp -o main.o $(CFLAGS)
random.o : $(RND)random.cpp $(RND)random.h
	$(CC) -c $(RND)random.cpp -o random.o $(CFLAGS)
functions.o : functions.cpp functions.h $(RND)random.h
	$(CC) -c functions.cpp -o functions.o $(CFLAGS)

clean :
	rm *.o main.exe seed.out
clean_results :
	rm *.out