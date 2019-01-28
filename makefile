CC=mpic++
CFLAGS= -I -O3 -Wall


DEPS= 
OBJ=integrate.o .o func.o mpi_integrate_v1.o mpi_integrate_v2.o mpi_integrate_v3.o 


all:  func integrate mpi_integrate_v1 mpi_integrate_v2 mpi_integrate_v3 

integrate:integrate.o func.o
	g++ -o $@ $^

mpi_integrate_v1: mpi_integrate_v1.o integrate.o func.o
	mpic++  -o $@ $^

mpi_integrate_v2: mpi_integrate_v2.o integrate.o  func.o
	$(CC) -o $@ $^

mpi_integrate_v3: mpi_integrate_v3.o integrate.o  func.o
	$(CC) -o $@ $^ $(CFLAGS) $(LIBS) mpi_integrate_v1.o


%.o: %.cpp $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS)

main: $(OBJ)
	$(CC) -O3 -o $@ $^

test1: integrate
	mpirun -np 1 integrate 1 4 100

test2: mpi_integrate_v1
	mpirun -np 4 ./mpi_integrate_v1 1 4 100

test3: mpi_integrate_v2 
	mpirun -np 4 ./mpi_integrate_v2 1 4 100

test4: mpi_integrate_v3 
	mpirun -np 4 ./mpi_integrate_v3 1 4 100

clean:
	rm -f *.o *~core
