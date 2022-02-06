#include <iostream>
#define MATH_USE_DEFINES
#include <cmath>
using namespace std;

double f(double x) {
    return (x * x * cos(2*x) + 1);
    //return (x * x - sin(x) - 0.25);
}

double LagrangePolynom (const double* nodes, const double* y, double x, int nodesCount) {
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

void FillFile(FILE* file, double a, double b, const double* nodes, const double* y, int nodesCount) {

    for (int i = 0; i <= 49; i++) {
        double xx = a + i * ((b - a) / 49.0);
        double yy = LagrangePolynom(nodes, y, xx, nodesCount);
        fprintf(file, "%.17lf;%.17lf\n", xx, yy);
    }
}

int main() {
    const char *tableValuesUniformFilename = "TableValuesUniformGrid.csv";
    FILE *tableValuesUniform = fopen(tableValuesUniformFilename, "w");
    if (tableValuesUniform == nullptr)
        return 0;
    const char *tableValuesChebFilename = "TableValuesChebGrid.csv";
    FILE *tableValuesCheb = fopen(tableValuesChebFilename, "w");
    if (tableValuesCheb == nullptr) {
        fclose(tableValuesUniform);
        return 0;
    }
    double a = -1.0, b = 2.5;
    for (int nodesCount = 5; nodesCount <= 60; nodesCount+=5) {
        auto *x = new double[nodesCount + 1];
        auto *y = new double[nodesCount + 1];
        for (int i = 0; i <= nodesCount; i++) {
            x[i] = a + i * ((b - a) / (double) nodesCount);
            //printf("%.17lf\n", x[i]);
            y[i] = f(x[i]);
        }
        FillFile(tableValuesUniform, a, b, x, y, nodesCount);

        for (int i = 0; i < nodesCount; i++) {
            //x[i] = cos(M_PI * (2 * i + 1) / (2 * nodesCount));
            x[i] = (b - a) * cos(M_PI * (2 * i + 1) / (2 * nodesCount)) / 2 + (a + b) / 2;
            //printf("%.17lf\n", x[i]);
            //cout << x[i] << endl;
            y[i] = f(x[i]);
            //cout << y[i] << endl;
        }
        FillFile(tableValuesCheb, a, b, x, y, nodesCount - 1);
        delete[] x;
        delete[] y;
    }
    fclose(tableValuesUniform);
    fclose(tableValuesCheb);
    return 0;
}
