#include <iostream>
#include <cmath>

typedef struct polynom {
    double a, b, c;
} polynom;

double f(double x) {
    return (x * x * cos(2*x) + 1);
}
double derf(double x) {
    return (2 * x * cos(2 * x) - 2 * x * x * sin(2 * x));
}

/*double QuadraticSplineMethod(double x0, double x1, double y0, double y1, double d0, double x, double& dergnext) {
    double a = (y1 - y0 - d0 * (x1 - x0))/((x1 - x0) * (x1 - x0));
    double b = d0 - 2 * a * x0;
    double c = y0 - a * x0 * x0 - b * x0;
    dergnext = 2 * a * x1 + b;
    return (a * x * x + b * x + c);
}*/

void QuadraticSplineMethod(const double x[], const double y[], polynom g[], int n, const double delta) {
    double dergCur = derf(x[0]);
    dergCur += delta * dergCur;
    for (int i = 0; i < n; i++) {
        g[i].a = (y[i+1] - y[i] - dergCur * (x[i+1] - x[i]))/((x[i+1] - x[i]) * (x[i+1] - x[i]));
        g[i].b = dergCur - 2 * g[i].a * x[i];
        g[i].c = y[i] - g[i].a * x[i] * x[i] - g[i].b * x[i];
        dergCur = 2 * g[i].a * x[i+1] + g[i].b;
    }
/*    double a = (y1 - y0 - d0 * (x1 - x0))/((x1 - x0) * (x1 - x0));
    double b = d0 - 2 * a * x0;
    double c = y0 - a * x0 * x0 - b * x0;
    dergnext = 2 * a * x1 + b;*/
}

void FillFile(FILE* file, double a, double b, const double* nodes, const double* y, int n, const double delta) {
    //double dergCur = derf(nodes[0]), dergNext = 0;
    double xCurrent = nodes[0];
    int numOfg = 0;
    double step = (b - a)/(double)n;
    polynom* g = new polynom[n];
    QuadraticSplineMethod(nodes, y, g, n, delta);
    if (n == 5) {
        for (int i = 0; i < n; i++) {
            std::cout << "a_" << i + 1 << " = " << g[i].a << "; b_" << i + 1 << " = " << g[i].b << "; c_" << i + 1
                      << " = " << g[i].c << std::endl;
        }
        std::cout << std::endl;
    }
    for (int i = 0; i <= 199; i++) {
        double xx = a + i * ((b - a) / 199.0);
        int number = (int)(abs((xx - a)/step));
        //if (abs(xx - b) <= 0.000001)
        if (xx == b)
            number = n - 1;
/*        if (xx >= xCurrent + step) {
            numOfg++;
            xCurrent = nodes[numOfg];
        }*/
        //double yy = g[numOfg].a * xx * xx + g[numOfg].b * xx + g[numOfg].c;
        double yy = g[number].a * xx * xx + g[number].b * xx + g[number].c;
        if (i == 199) {
            std::cout << "num = " << number << " ||| " << g[number].a << " " << g[number].b << " " << g[number].c << std::endl;
        }
        fprintf(file, "%.17lf;%.17lf\n", xx, yy);
    }
/*    for (int i = 0; i <= 99; i++) {
        double xx = a + i * ((b - a) / 99.0);
        //double step = (b - a)/(double)n;
        //int number = (int)(abs((xx - a)/step)) + 1;
        if (xx >= xCurrent + step) {
            numOfX++;
            xCurrent = nodes[numOfX];
            dergCur = dergNext;
        }
        double yy = QuadraticSplineMethod(nodes[numOfX], nodes[numOfX + 1], y[numOfX], y[numOfX + 1], dergCur, xx, dergNext);
        fprintf(file, "%.17lf;%.17lf\n", xx, yy);
    }*/
}

int main() {
    const char* QuadSplineFileName = "QuadSpline.csv";
    FILE* QuadSpline = fopen(QuadSplineFileName, "w");
    if (!QuadSpline) {
        std::cout << "Error in opening file" << std::endl;
        return -1;
    }
    double a = -2.0, b = 2.0;
    //for (int n = 3; n <= 7; n+=2) {
    for (int n = 5; n <= 180; n+=5) {
        auto* x = new double [n + 1];
        auto* y = new double [n + 1];
        for (int i = 0; i <= n; i++) {
            x[i] = a + i * ((b - a) / (double)n);
            y[i] = f(x[i]);
        }
        FillFile(QuadSpline, a, b, x, y, n, 0);
        delete[] x;
        delete[] y;
    }
    fclose(QuadSpline);
    const char* PerturbatedSplineFileName = "PerturbatedSpline.csv";
    FILE* PerturbatedSpline = fopen(PerturbatedSplineFileName, "w");
    if (!PerturbatedSpline) {
        std::cout << "Error in opening file" << std::endl;
        return -1;
    }
    int n = 20;
    auto* x = new double [n + 1];
    auto* y = new double [n + 1];
    for (double delta = 0.0000001; delta <= 1000.0; delta *= 10.0) {
        for (int i = 0; i <= n; i++) {
            x[i] = a + i * ((b - a) / (double)n);
            y[i] = f(x[i]);
        }
        FillFile(PerturbatedSpline, a, b, x, y, n, delta);
    }
    delete[] x;
    delete[] y;
    fclose(PerturbatedSpline);
    return 0;
}