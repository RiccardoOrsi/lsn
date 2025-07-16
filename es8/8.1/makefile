CC = g++
CFLAGS = -Wall -O3 --std=c++11
RND = ../../rnd_gen/
LIB = ../../librerie/


main.exe : main.o random.o librerie.o
	$(CC) random.o librerie.o main.o -o main.exe
main.o : main.cpp functions.h $(LIB)librerie.h
	$(CC) -c main.cpp -o main.o $(CFLAGS)
random.o : $(RND)random.cpp $(RND)random.h
	$(CC) -c $(RND)random.cpp -o random.o $(CFLAGS)
librerie.o : $(LIB)librerie.cpp $(LIB)librerie.h
	$(CC) -c $(LIB)librerie.cpp -o librerie.o $(CFLAGS)

clean :
	rm *.o main.exe seed.out
clean_results :
	rm OUTPUT/*.*