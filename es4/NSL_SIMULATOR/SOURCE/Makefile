CC = g++
CFLAGS = -O3 --std=c++11
AFLAGS = -larmadillo
all: simulator.exe
simulator.exe : system.o NSL_SIMULATOR.o particle.o random.o
	$(CC) system.o particle.o random.o NSL_SIMULATOR.o -o simulator.exe $(AFLAGS)
NSL_SIMULATOR.o : NSL_SIMULATOR.cpp system.h particle.h
	$(CC) -c NSL_SIMULATOR.cpp -o NSL_SIMULATOR.o $(CFLAGS)
system.o : system.cpp system.h random.h particle.h
	$(CC) -c system.cpp -o system.o $(CFLAGS)
particle.o : particle.cpp particle.h
	$(CC) -c particle.cpp -o particle.o $(CFLAGS)
random.o : random.cpp random.h
	$(CC) -c random.cpp -o random.o $(CFLAGS)
clean :
	rm *.o simulator.exe
remove_gas:
	rm ../OUTPUT/gas/*.*
	rm ../OUTPUT/gas/CONFIG/*.*
remove_liquid:
	rm ../OUTPUT/liquid/*.*
	rm ../OUTPUT/liquid/CONFIG/*.*
remove_solid:
	rm ../OUTPUT/solid/*.*
	rm ../OUTPUT/solid/CONFIG/*.*
remove:
	rm ../OUTPUT/gas/*.* ../OUTPUT/gas/CONFIG/*.* ../OUTPUT/solid/*.* ../OUTPUT/solid/CONFIG/*.* ../OUTPUT/liquid/*.* ../OUTPUT/liquid/CONFIG/*.*
remove_t:	
	rm ../OUTPUT/tgas/*.* ../OUTPUT/tgas/CONFIG/*.* ../OUTPUT/tsolid/*.* ../OUTPUT/tsolid/CONFIG/*.* ../OUTPUT/tliquid/*.* ../OUTPUT/tliquid/CONFIG/*.*
