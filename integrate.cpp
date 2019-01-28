#include <iostream>
#include <stdio.h>
#include <sstream>
#include <string.h>

using namespace std;

float f(float x) {
    //    x^2+3x+10
    return ((x * x) + (3 * x) + 10);
}

int main(int argc, char* argv[]) {

    if (argc < 4) {
        printf("You must pass 3 parameters a, b, and n\n");
        return 0;
    }

    float a, b;
    int n = 0;
    float h, approx;

    string s1(argv[1]);
    string s2(argv[2]);
    string s3(argv[3]);
    stringstream geek1(s1);
    geek1 >> a;
    stringstream geek2(s2);
    geek2 >> b;
    stringstream geek3(s3);
    geek3 >> n;

    float *x = new float[n];
    x [0] = a;
    x [n - 1] = b;

    h = (b - a) / n;

    approx = (f(a) + f(b)) / 2;

    for (int i = 1; i < n; i++) {
        x[i] = a + (i * h);
        approx += f(x[i]);
    }

    approx = h*approx;

    printf("with n = %d trapezoids, our estimate\n", n);
    printf("of the integral form %f to %f = %.15e\n", a, b, approx);

    return 0;
}
