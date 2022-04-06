#include <iostream>
#include <cmath>

double f(double x) {
    return (x * x * cos(2.0 * x) + 1.0);
}

double mapping(double x, double a, double b) {
    return ((a + b + x * (b - a)) / 2.0);
}

void GaussMethod (double a, double b, FILE* file) {
    for (double eps = 0.000001; eps <= 0.1; eps *= 10) {
        unsigned long long int n = 1;
        double I1 = 0, I2 = 0, a1 = a, b1 = b;
        I2 = 1.0 / 6.0 * (5.0 * f(mapping(-sqrt(3.0/5.0), a, b)) + 8.0 * f(mapping(0.0, a, b)) + 5.0 * f(mapping(sqrt(3.0/5.0), a, b)));
        double av1 = 0, av2 = 0;
        do {
            //av1 = (I1+I2)/(double)n;
            I1 = I2;
            n *= 2;
            double sum = 0;
            for (int i = 0; i < n; ++i) {
                double h = (b - a) / (double)n;
                double a2 = a + i * h, b2 = a + (i + 1) * h;
                sum += 1.0 / 6.0 * (5.0 * f(mapping(-sqrt(3.0/5.0), a2, b2)) + 8.0 * f(mapping(0.0, a2, b2)) + 5.0 * f(mapping(sqrt(3.0/5.0), a2, b2)));
            }
            I2 = sum/(double)n;
            //av2 = (I1+I2)/(double)n;
        } while (abs(I2 - I1) > 7.0 * eps);
        fprintf(file, "%.17lf;%llu;%.17lf\n", eps, n, I2);
    }
}

int main() {
    const char* Gaussfilename = "Gauss.csv";
    FILE* Gauss = fopen(Gaussfilename, "w");
    if(!Gauss)
        return -1;
    double a = 0, b = 3;
    GaussMethod(a, b, Gauss);
    return 0;
}
