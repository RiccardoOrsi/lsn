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
remove_2:
	rm ../OUTPUT/7.2/GAS/*.* ../OUTPUT/7.2/GAS/CONFIG/*.* ../OUTPUT/7.2/LIQUID/*.* ../OUTPUT/7.2/LIQUID/CONFIG/*.* ../OUTPUT/7.2/SOLID/*.* ../OUTPUT/7.2/SOLID/CONFIG/*.* 
remove_NVT:
	rm ../OUTPUT/7.4/NVT/GAS/*.* ../OUTPUT/7.4/NVT/GAS/CONFIG/*.* ../OUTPUT/7.4/NVT/LIQUID/*.* ../OUTPUT/7.4/NVT/LIQUID/CONFIG/*.* ../OUTPUT/7.4/NVT/SOLID/*.* ../OUTPUT/7.4/NVT/SOLID/CONFIG/*.* 
remove_NVE:
	rm ../OUTPUT/7.4/NVE/GAS/*.* ../OUTPUT/7.4/NVE/GAS/CONFIG/*.* ../OUTPUT/7.4/NVE/LIQUID/*.* ../OUTPUT/7.4/NVE/LIQUID/CONFIG/*.* ../OUTPUT/7.4/NVE/SOLID/*.* ../OUTPUT/7.4/NVE/SOLID/CONFIG/*.* 