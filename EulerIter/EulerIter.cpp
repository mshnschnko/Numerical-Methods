#pragma warning(disable:4996)
#include <cmath>
#include <iostream>
#include <fstream>
#include <vector>
#define A 0
#define B 4
#define F_A 1

using namespace std;

int k;

double f(double x, double y) {
    k++;
    return ((4 * x + 2 * y) / (2 * x + 1));
}

double f_exact(double x) {
    return ((2 * x + 1) * log(2 * x + 1) + 1);
}

void CreateGrid(double a, double b, int n, vector <double>& x) {
    //double* net = (double*)calloc(n + 1, sizeof(double));
    double h = (b - a) / n;
    for (int i = 0; i <= n; ++i)
        x.push_back(a + h * i);
}

void WriteResult(vector<double>& y, FILE* file) {
    fprintf(file, "%i;", (int)(y.size() - 1));
    for (int i = 0; i < y.size(); ++i)
        fprintf(file, "%.17lf;", y[i]);
    fprintf(file, "\n");
}

void WriteParcialResult(vector<double>& y, FILE* file) {
    fprintf(file, "%i;%.17lf;%.17lf;%i\n", (int)(y.size() - 1), y.at(1), y.back(), k);
}

double EulerStep(double x, double y, double h) {
    return (y + h * f(x, y));
}

vector <double> EulerIter(int n, double f_a) {
    double h = (B - A) / (double)n;
    vector <double> x;
    CreateGrid(A, B, n, x);
    vector <double> y;
    double y_k = f_a, y_k_n;
    y.push_back(y_k);
    for (int i = 1; i <= n; ++i) {
        y_k_n = EulerStep(x[i-1], y_k, h);
        for (int j = 0; j < 5; ++j)
            y_k_n = y_k + h / 2.0 * (f(x[i - 1], y_k) + f(x[i], y_k_n));
        y.push_back(y_k_n);
        y_k = y_k_n;
    }
    return y;
    //WriteResult(y, file);
}

//vector <double> EulerIter(int n, double f_a, FILE* file) {
//    double h = (B - A) / (double)n;
//    vector <double> x;
//    CreateGrid(A, B, n, x);
//    vector <double> y;
//    double y_k = f_a, y_k_n;
//    y.push_back(y_k);
//    for (int i = 1; i <= n; ++i) {
//        y_k_n = EulerStep(x[i - 1], y_k, h);
//        cout << "y Euler = " << y_k_n << endl;
//        cout << "y iter:\t";
//        for (int j = 0; j < 3; ++j) {
//            y_k_n = y_k + h / 2.0 * (f(x[i - 1], y_k) + f(x[i], y_k_n));
//            cout << y_k_n << " ";
//        }
//        cout << endl;
//        y.push_back(y_k_n);
//        y_k = y_k_n;
//    }
//    return y;
//    //WriteResult(y, file);
//}

int main() {
    FILE* fileOnce = fopen("EulerIterOnce.csv", "w");
    if (!fileOnce) {
        perror("Error in opening file!");
        return -1;
    }
    int n = 20;
    k = 0;
    vector <double> y1 = EulerIter(n, F_A);
    WriteResult(y1, fileOnce);

    n = 10;
    k = 0;
    y1.clear();
    y1 = EulerIter(n, F_A);
    WriteResult(y1, fileOnce);
    fclose(fileOnce);

    FILE* file = fopen("EulerIter.csv", "w");
    if (!file) {
        perror("Error in opening file!");
        return -1;
    }
    for (n = 500; n >= 10; n -= 10) {
        k = 0;
        vector <double> y = EulerIter(n, F_A);
        WriteParcialResult(y, file);
    }
    fclose(file);

    FILE* fileOutragePlus = fopen("EulerIterOutragePlus.csv", "w");
    if (!fileOutragePlus) {
        perror("Error in opening file!");
        return -1;
    }
    FILE* fileOutrageMinus = fopen("EulerIterOutrageMinus.csv", "w");
    if (!fileOutrageMinus) {
        perror("Error in opening file!");
        return -1;
    }
    n = 25;
    for (double delta = 0.00000000000001; delta <= 0.1; delta *= 10) {
        k = 0;
        double f_a = F_A * (1 + delta);
        vector <double> y = EulerIter(n, f_a);
        WriteParcialResult(y, fileOutragePlus);
        
        y.clear();
        k = 0;
        f_a = F_A * (1 - delta);
        y = EulerIter(n, f_a);
        WriteParcialResult(y, fileOutrageMinus);
    }
    fclose(fileOutragePlus);
    fclose(fileOutrageMinus);
    return 0;
}