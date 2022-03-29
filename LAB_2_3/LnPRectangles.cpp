#include <iostream>
#include <cmath>

enum Side {left = 0, right = 1};

static int dots = 0, dots_opt = 0;

double f(double x) {
    return (x * x * cos(2*x) + 1);
}

/*double Rectangle(const double a, const double b, unsigned long long int n, int side) {
    double h = (b-a)/n;
    double sum = 0;
    for (int i = 0; i < n; i++)
        sum += f(a + (i + side) * h);
    return (h * sum);
}*/

/*double Rectangle(const double a, const double b, unsigned long long int n, int side, double h, double I) {
    if (n == 1) {
        dots_opt += 2;
        return ((b-a)*f(a + (side * (b-a))));
    }
    double sum = 0;
    double x = a + ((b - a) / (double)n);
    for (int i = 0; i < n / 2; ++i) {
        sum += f(x) * (b - a) / (double)n;
        x += 2 * (b - a) / (double)n;
        dots_opt++;
    }
    return (I*0.5+sum);
}*/

/*void FillFile(const double a, const double b, int side, FILE* file) {
    double I1, I2;
    unsigned long long int n;
    for (double e = 0.00001; e <= 0.1; e *= 10.0) {
        n = 1;
        I1 = Rectangle(a, b, n, side);
        I2 = Rectangle(a, b, 2*n, side);
        while (abs(I2 - I1) > e) {
            I1 = I2;
            n *= 2;
            I2 = Rectangle(a, b, 2*n, side);
        }
        fprintf(file, "%.17lf;%llu;%.17lf\n", e, n, I2);
        //std::cout << "Integral " << side << " = " << (I2 + I1)/2.0 << " n = " << n << " e = " << e << std::endl;
    }
}*/

/*void FillFile(const double a, const double b, int side, FILE* file) {
    double I1, I2;
    unsigned long long int n;
    for (double e = 0.000001; e <= 0.1; e *= 10.0) {
        n = 1;
        double h = (b-a)/n;
        I1 = Rectangle(a, b, n, side);
        I2 = Rectangle(a+0.5*h, b-0.5*h, n, side)/2.0 + I1/2.0;
        while (abs(I2 - I1) >= e) {
            I1 = I2;
            n *= 2;
            h = (b-a)/n;
            I2 = Rectangle(a+0.5*h, b-0.5*h, n, side)/2.0 + I1/2.0;
            std::cout << "Integral " << side << " = " << I2 << " n = " << n << " e = " << e << std::endl;
        }
        fprintf(file, "%.17lf;%llu;%.17lf\n", e, n, I2);
//        std::cout << "Integral " << side << " = " << (I2 + I1)/2.0 << " n = " << n << " e = " << e << std::endl;
    }
}*/

/*void FillFile(const double a, const double b, int side, FILE* file) {
    unsigned long long int n = 1;
    double prev = 0, cur;
    for (double e = 0.00001; e <= 0.1; e *= 10) {
        do {
            if (n != 1) prev = cur;
            cur = Rectangle(a, b, n, side, (b-a)/(double)n, prev);
            n *= 2;
        } while (abs(cur - prev) > e);
        fprintf(file, "%.17lf;%llu;%.17lf\n", e, n, cur);
    }
}*/

double Formula(double a, double b, unsigned long long int n, int side) {
    double sum = 0; //= f(a) + f(b);
    //dots += 2;
    double h = (b - a)/(double)n;
    for (int i = 0; i < n; ++i) {
        double x = a + (i + side) * h;
        sum += f(x);
        dots++;
    }
    return h * sum;
}

void Method(double a, double b, int side, FILE* file) {
    for (double eps = 0.000001; eps <= 0.1; eps *= 10) {
        dots = 0;
        unsigned long long int n = 1;
        double prev = 0;
        double curr = Formula(a, b, n, side);
        do {
            n *= 2;
            prev = curr;
            curr = Formula(a, b, n, side);
        } while (fabs(curr - prev) > 3 * eps);
        fprintf(file, "%.17lf;%llu;%i;%.17lf\n", eps, n, dots, curr);
    }
}

double Formula_opt(double a, double b, unsigned long long int n, int side, double I) {
    if (n == 1) {
        dots_opt += 1;
        double h = (b - a);
        return (h * f(a + side * h));
    }
    double sum = 0;
    double h = (b - a)/(double)n;
    double x = a + h;
    for (int i = 0; i < n / 2; ++i) {
        sum += f(x) * h;
        x += 2 * h;
        //double x = a + h * (2 * i + side);
        //sum += f(x) * h;
        dots_opt++;
    }
    return (I * 0.5 + sum);
}

void Method_opt(double a, double b, int side, FILE* file) {
    for (double eps = 0.000001; eps <= 0.1; eps *= 10) {
        dots_opt = 0;
        unsigned long long int n = 1;
        double prev = 0, curr;
        do {
            if (n != 1) prev = curr;
            curr = Formula_opt(a, b, n, side, prev);
            n *= 2;
        } while (fabs(curr - prev) > 3 * eps);
        fprintf(file, "%.17lf;%llu;%i;%.17lf\n", eps, n/2, dots_opt, curr);
    }
}

int main() {
    const char* leftFileName = "LeftRectangle.csv";
    const char* rightFileName = "RightRectangle.csv";
    FILE* LeftFile = fopen(leftFileName, "w");
    if(!LeftFile)
        return -1;
    FILE* RightFile = fopen(rightFileName, "w");
    if(!RightFile) {
        fclose(LeftFile);
        return -1;
    }
    const char* leftOptFileName = "LeftRectangleOpt.csv";
    const char* rightOptFileName = "RightRectangleOpt.csv";
    FILE* LeftFileOpt = fopen(leftOptFileName, "w");
    FILE* RightFileOpt = fopen(rightOptFileName, "w");
    double a = 0, b = 3;
    std::cout << "LEFT : " << std::endl << std::endl;
    Method(a, b, left, LeftFile);
    std::cout << "RIGHT : " << std::endl << std::endl;
    Method(a, b, right, RightFile);
    std::cout << "LEFT OPT: " << std::endl << std::endl;
    Method_opt(a, b, left, LeftFileOpt);
    std::cout << "RIGHT OPT: " << std::endl << std::endl;
    Method_opt(a, b, right, RightFileOpt);
    fclose(LeftFile);
    fclose(RightFile);
    fclose(LeftFileOpt);
    fclose(RightFileOpt);
    return 0;
}