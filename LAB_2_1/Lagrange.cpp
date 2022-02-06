#include <iostream>
#include <math.h>
using namespace std;

double f(double x) {
    return (x * x - sin(x)-0.25);
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

int main() {
    int nodesCount = 4;
    double a = 0.0, b = 2.0;
    auto* x = new double [nodesCount + 1];
    auto* y = new double [nodesCount + 1];
    for (int i = 0; i <= nodesCount; i++) {
        x[i] = a + i * ((b - a) / (double)nodesCount);
        y[i] = f(x[i]);
    }
    const char* tableValuesFilename = "TableValues.csv";
    FILE* tableValues = fopen(tableValuesFilename, "w");
    FillFile(tableValues, )
    cout << LagrangePolynom(x, y, 1.8, nodesCount);
/*    for (int i = 0; i <= nodesCount; i++) {
        cout << x[i] << endl;
        cout << y[i] << endl;
    }*/
    return 0;
}
