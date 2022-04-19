#include <cmath>
#include <iostream>
#include <fstream>
#define A 0
#define B 4
#define F_A 1

double f(double x, double y) {
    return ((4*x+2*y)/(2*x+1));
}

double f_exact(double x) {
    return ((2*x+1)*log(2*x+1)+1);
}

double* CreateGrid(double a, double b, int n) {
    double* net = (double*)calloc(n + 1, sizeof(double));
    double h = (b - a) / n;
    for (int i = 0; i <= n; ++i)
        net[i] = a + h * i;
    return net;
}

double* Euler(double a, double b, int n, double f_a) {
    double* net = CreateGrid(a, b, n);
    double h = (b - a) / n;
    double* y = (double*)calloc(n + 1, sizeof(double));
    y[0] = f_a;
    for (int i = 1; i <= n; ++i)
        y[i] = y[i - 1] + h * f(net[i - 1], y[i - 1]);
    free(net);
    return y;
}

int Error(double y_2h, double y_h, double epsl) {
    if (fabs(y_2h - y_h) > epsl)
        return 1;
    return 0;
}

double StepEuler_Runge(double x, double h, double y_0, int &k) {
    k++;
    return y_0 + h * f(x, y_0);
}

double Euler_Runge(double a, double b, double epsl, int& n, double f_a, int& k) {
    double x = a;
    double h = (b - a);
    double y_0 = f_a;
    double y_h = StepEuler_Runge(x, h, y_0, k);
    double y_2h = StepEuler_Runge(x, h / 2, y_0, k);
    double y_prev = y_0;
    int iter = 1;
    while (x <= b) {
        while (Error(y_2h, y_h, epsl)) {
            h = h / 2;
            iter++;
            y_h = y_2h;
            y_prev = y_0;
            for (int i = 0; i < pow(2, iter); ++i) {
                y_2h = StepEuler_Runge(x+(h/2)*i, h/2, y_prev,k);
                y_prev = y_2h;
            }
        }
        x += h;
        y_0 = y_h;
        iter = 1;
    }
    return y_2h;
}

int main() {
    std::ofstream out;
    std::ofstream out1;
    FILE* out22 = fopen("Y_one.csv", "w");
    //out.open("Y_one.csv");
    int n1 = 25;
    double* y = Euler(A, B, n1, F_A);
    double* net = CreateGrid(A, B, n1);
    for (int i = 0; i <= n1; ++i) {
        //out.precision(15);
        //out << net[i] << ";" << y[i] << "\n";
        fprintf(out22, "%.17lf;%.17lf\n", net[i], y[i]);
    }
    free(y);
    fclose(out22);

    //out.close();
    out22 = fopen("Y.csv", "w");
    //out.open("Y.csv");
    for (int n = 10; n <= 500; ++n) {
        double* y = Euler(A, B, n, F_A);
        //out.precision(15);
        //out << y[1] << ";" << y[n] << ";";
        //out << "\n";
        fprintf(out22, "%i;%.17lf;%.17lf\n", n, y[1], y[n]);
        free(y);
    }
    //out.close();
    fclose(out22);
    printf("vso");
    FILE* RungeFile = fopen("Runge.csv", "w");
//    out.open("Runge.csv");
//    out1.open("Count.csv");
    for (double epsl = 0.1; epsl >= 1e-6; epsl = epsl / 10) {
        int n = 1;
        int k = 0;
        double y = Euler_Runge(A, B, epsl, n, F_A, k);
        fprintf(RungeFile, "%.17lf;%i;%i;%.17lf\n", epsl, n, k, y);
//        out.precision(15);
//        out << y << ";";
//        out << "\n";
//        out1 << k << ";";
//        out1 << "\n";
    }
    fclose(RungeFile);
//    out.close();
//    out1.close();
    return 0;
}