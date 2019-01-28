#include <mpi.h>
#include <cstdlib>
#include <string.h>
#include <sstream>

using namespace std;

float func(float x){
	return (x*x)+(3*x) + 10;
}

float Trap(float *x, int n) {

    float estimate, y;
    int i;

    estimate = (func(x[0]) + func(x[1])) / 2.0;

    for (i = 1; i <= n - 1; i++) {
        y = x[0] + i * x[2];
        estimate += func(y);
    }
    estimate = estimate * x[2];
    return estimate;
}

int main(int argc, char* argv[]) {

    if (argc < 4) {
        printf("You must pass 3 parameters a, b, and n\n");
        return 0;
    }

    int my_rank, comm_sz, n = 1024, local_n;
    double local_int, total_int;
    double a = 0.0, b = 3.0, h, local_a, local_b;
    int source;
    int buffer;
    int const root = 0;

    string s1(argv[1]);
    string s2(argv[2]);
    string s3(argv[3]);
    stringstream geek1(s1);
    geek1 >> a;
    stringstream geek2(s2);
    geek2 >> b;
    stringstream geek3(s3);
    geek3 >> n;


    MPI_Init(NULL, NULL);
    MPI_Comm_rank(MPI_COMM_WORLD, &my_rank);
    MPI_Comm_size(MPI_COMM_WORLD, &comm_sz);

    h = (b - a) / n;
    local_n = n / comm_sz;

    local_a = a + my_rank * local_n*h;
    local_b = local_a + local_n*h;

    float x[3];
    x[0] = local_a;
    x[1] = local_b;
    x[2] = h;

    local_int = Trap(x, local_n);

    if (my_rank != root) {
        MPI_Send(&local_int, 1, MPI_DOUBLE, 0, 0, MPI_COMM_WORLD);
    } else {
        total_int = local_int;
	buffer = local_int;
        for (source = 1; source < comm_sz; source++) {
	    MPI_Bcast(&buffer, 1, MPI_INT, root, MPI_COMM_WORLD);
            total_int += local_int;
        }
    }

    if (my_rank == 0) {
        printf("with n = %d trapezoids, our estimate\n", n);
        printf("of the integral form %f to %f = %.15e\n", a, b, total_int);
    }
    MPI_Finalize();
    return 0;
}

