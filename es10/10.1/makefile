
CXX = mpicxx
RND = ../../rnd_gen/
NP = 4

# Regola principale
all: main.exe

# Link esplicito dei file oggetto
main.exe: main.o functions.o random.o
	$(CXX) -o main.exe main.o functions.o random.o

# Compilazione esplicita dei sorgenti
main.o: main.cpp functions.h
	$(CXX) -c main.cpp -o main.o

functions.o : functions.cpp functions.h $(RND)random.h
	$(CXX) -c functions.cpp -o functions.o

random.o : $(RND)random.cpp $(RND)random.h
	$(CXX) -c $(RND)random.cpp -o random.o

# Pulizia
clean:
	rm *.o *.out *.exe

run: main.exe
	mpirun -np $(NP) ./main.exe
