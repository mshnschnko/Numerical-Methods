#include <iostream>
#define MATH_USE_DEFINES
#include <cmath>

double f(double x) {
    return (x * x * cos(2*x) + 1);
}
double derf(double x) {
    return (2 * x * cos(2 * x) - 2 * x * x * sin(2 * x));
}

double QuadraticSplineMethod(double x0, double x1, double y0, double y1, double d0, double x, double& dergnext) {
    double a = (y1 - y0 - d0 * (x1 - x0))/((x1 - x0) * (x1 - x0));
    double b = d0 - 2 * a * x0;
    double c = y0 - a * x0 * x0 - b * x0;
    dergnext = 2 * a * x1 + b;
    return (a * x * x + b * x + c);
}

void FillFile(FILE* file, double a, double b, const double* nodes, const double* y, int n) {
    double dergCur = derf(nodes[0]), dergNext = 0;
    double xCurrent = nodes[0];
    int numOfX = 0;
    for (int i = 0; i <= 99; i++) {
        double xx = a + i * ((b - a) / 99.0);
        double step = (b - a)/(double)n;
        //int number = (int)(abs((xx - a)/step)) + 1;
        if (xx >= xCurrent + step) {
            numOfX++;
            xCurrent = nodes[numOfX];
            dergCur = dergNext;
        }
        double yy = QuadraticSplineMethod(nodes[numOfX], nodes[numOfX + 1], y[numOfX], y[numOfX + 1], dergCur, xx, dergNext);
        fprintf(file, "%.17lf;%.17lf\n", xx, yy);
    }
}

int main() {
    const char* QuadSplineFileName = "QuadSpline.csv";
    FILE* QuadSpline = fopen(QuadSplineFileName, "w");
    if (!QuadSpline) {
        std::cout << "Error in opening file" << std::endl;
        return -1;
    }
/*    try {
        FILE* QuadSpline = fopen(QuadSplineFileName, "w");
        if (!QuadSpline)
            throw std::string("Error in opening file");
    }
    catch (const std::string& err){
        std::cout << err << std::endl;
        return -1;
    }*/
    double a = -2.0, b = 2.0;
    for (int n = 5; n <= 60; n+=5) {
        auto* x = new double [n + 1];
        auto* y = new double [n + 1];
        for (int i = 0; i <= n; i++) {
            x[i] = a + i * ((b - a) / (double)n);
            y[i] = f(x[i]);
        }
        FillFile(QuadSpline, a, b, x, y, n);
    }
    fclose(QuadSpline);
    return 0;
}