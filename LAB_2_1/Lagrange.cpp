#include <iostream>
#include <cstdlib>
#define MATH_USE_DEFINES
#include <cmath>
using namespace std;

double f(double x) {
    return (x * x * cos(2*x) + 1);
    //return (x * x - sin(x) - 0.25);
    //return (x * x * x - exp(x) + 1);
}

int factorial(int x) {
    int fact = 1;
    for (int i = 1; i <= x; i++) {
        fact *= i;
    }
    return fact;
}

double LagrangePolynom(const double* nodes, const double* y, double x, int nodesCount) {
    double multiply = 1;
    double sum = 0;
    for (int i = 0; i <= nodesCount; i++) {
        for (int k = 0; k <= nodesCount; k++) {
            if (k != i) {
                multiply *= (x - nodes[k]) / (nodes[i] - nodes[k]);
            }
        }
        sum += y[i] * multiply;
        multiply = 1;
    }
    return sum;
}

double LagrangeForUniform(const double* y, double x, int nodesCount, double t) {
    double multiply = 1;
    double sum = 0;
    int minus = 0;
    for (int i = 0; i <= nodesCount; i++) {
/*        for (int k = 0; k <= nodesCount; k++)
            multiply *= t - k;
        if (multiply == 0) {
            multiply = 1;
            continue;
        }*/
        //minus = (nodesCount - i) % 2 == 0 ? 1 : -1;
        //sum += y[i] * (minus * multiply) / factorial(i) / factorial(nodesCount - i) / (t - i);
        for (int k = 0; k <= nodesCount; k++) {
            if (k != i)
                multiply *= (t - k)/(i - k);
        }
        sum += y[i] * multiply;
        multiply = 1;
    }
    return sum;
}

void FillFile(FILE* file, double a, double b, const double* nodes, const double* y, int nodesCount) {

    for (int i = 0; i <= 99; i++) {
        double xx = a + i * ((b - a) / 99.0);
        double yy = LagrangePolynom(nodes, y, xx, nodesCount);
        fprintf(file, "%.17lf;%.17lf\n", xx, yy);
    }
}

void FillForUniform(FILE* file, double a, double b, const double* y, int nodesCount) {
    double h = ((b - a) / (double) nodesCount);
    for (int i = 0; i <= 99; i++) {
        double xx = a + i * ((b - a) / 99.0);
        double t = (xx - a) / h;
        double yy = LagrangeForUniform(y, xx, nodesCount, t);
        fprintf(file, "%.17lf;%.17lf\n", xx, yy);
    }
}

int main() {
    const char *tableValuesUniformFilename = "TableValuesUniformGrid.csv";
    FILE* tableValuesUniform = fopen(tableValuesUniformFilename, "w");
    if (tableValuesUniform == nullptr)
        return 0;
    const char *tableValuesChebFilename = "TableValuesChebGrid.csv";
    FILE* tableValuesCheb = fopen(tableValuesChebFilename, "w");
    if (tableValuesCheb == nullptr) {
        fclose(tableValuesUniform);
        return 0;
    }
    const char *tableValuesUniSpecFilename = "TableValuesUniSpecGrid.csv";
    FILE* tableValuesUniSpec = fopen(tableValuesUniSpecFilename, "w");
    if (tableValuesUniSpec == nullptr) {
        fclose(tableValuesUniform);
        fclose(tableValuesCheb);
        return 0;
    }
    double a = -2.0, b = 2.0;
//    for (int nodesCount = 5; nodesCount <= 60; nodesCount+=5) {
    for (int nodesCount = 3; nodesCount <= 7; nodesCount+=2) {
            auto *x = new double[nodesCount + 1];
            auto *y = new double[nodesCount + 1];
            for (int i = 0; i <= nodesCount; i++) {
                x[i] = a + i * ((b - a) / (double) nodesCount);
                //printf("%.17lf\n", x[i]);
                y[i] = f(x[i]);
            }
            FillFile(tableValuesUniform, a, b, x, y, nodesCount);
            FillForUniform(tableValuesUniSpec, a, b, y, nodesCount);
//            auto *x1 = new double[nodesCount + 1];
//            auto *y1 = new double[nodesCount + 1];
            for (int i = 0; i <= nodesCount; i++) {
                //x[i] = cos(M_PI * (2 * i + 1) / (2 * nodesCount));
                x[i] = (double)(b - a) * cos(M_PI * (double)(2.0 * i + 1.0) / (2.0 * (double)nodesCount + 2.0)) / 2.0 + (double(a + b) / 2.0);
                //printf("%.17lf\n", x[i]);
                //cout << x[i] << endl;
                y[i] = f(x[i]);
                //cout << y[i] << endl;
            }
            FillFile(tableValuesCheb, a, b, x, y, nodesCount);
            delete[] x;
            delete[] y;
//            delete[] x1;
//            delete[] y1;
        }
    fclose(tableValuesUniform);
    fclose(tableValuesCheb);
    return 0;
}