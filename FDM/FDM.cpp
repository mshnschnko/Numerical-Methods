#pragma warning(disable:4996)
#include <iostream>
#include <windows.h>
#include <cmath>

#define _CRT_SECURE_NO_WARNINGS

using namespace std;

double alpha0 = 2;
double alpha1 = -2.5;
double A = 2;
double beta0 = 3;
double beta1 = 0;
double B = 3 / exp(1);
/*double alpha0 = 1;
double alpha1 = 0;
double A = 1;
double beta0 = 1;
double beta1 = 0;
double B = 1 / exp(1);*/
double a0 = 0;
double b0 = 1;

void SolveMatrix(int n, double* a, double* c, double* b, double* f, double* x);

void FillBoard(int n, const double* X, double h, double* w1, double* w2, double* w3);

double* FillF(const double* const X, int n, double h);

void WriteResult(const double* const xr, int n, FILE* fp)
{
	fprintf(fp, "%i;", n);
	for (int i = 0; i < n; i++)
	{
		fprintf(fp, "%.17lf;", xr[i]);
	}
	fprintf(fp, "\n");
}

void WriteResultA(const double* const xr, int n, const char* filename)
{
	FILE* fp;
	if ((fp = fopen(filename, "a")) == NULL)
	{
		printf("Не удалось открыть файл");
		return;
	}
	for (int i = 0; i < n; i++)
	{
		fprintf(fp, "%.17lf;", xr[i]);
	}
	fprintf(fp, "\n");
	fclose(fp);
}

double p(double x)
{
	return 4 * x;
}

double q(double x)
{
	return (4 * x * x + 3);
}

double f(double x)
{
	return exp(-x * x);
}

void FillBoard(int n, const double* X, double h, double* w1, double* w2, double* w3)
{
	w1[0] = alpha1;
	w2[0] = alpha0 * h - alpha1;
	w3[0] = 0;
	for (int i = 1; i < n; i++)
	{
		w1[i] = 1 + h * p(X[i]) / 2;
		w2[i] = h * h * q(X[i]) - 2;
		w3[i] = 1 - h * p(X[i]) / 2;
	}
	w1[n] = 0;
	w2[n] = beta0 * h + beta1;
	w3[n] = -beta1;
	return;
}

double* FillF(const double* const X, int n, double h)
{
	double* F = new double[n + 1]; //vector F[n+1]
	for (int i = 1; i < n; i++)
	{
		F[i] = h * h * f(X[i]);
	}
	F[0] = h * A;
	F[n] = h * B;
	return F;
}

void SolveMatrix(int n, double* a, double* c, double* b, double* f, double* x)
{
	double m;
	for (int i = 1; i < n; i++)
	{
		m = a[i] / c[i - 1];
		c[i] = c[i] - m * b[i - 1];
		f[i] = f[i] - m * f[i - 1];
	}

	x[n - 1] = f[n - 1] / c[n - 1];

	for (int i = n - 2; i >= 0; i--)
	{
		x[i] = (f[i] - b[i] * x[i + 1]) / c[i];
	}
}


int main()
{
	//===
	FILE* fp;
	if ((fp = fopen("Unew.csv", "w")) == NULL)
	{
		printf("Не удалось открыть файл");
		return -1;
	}

	for (int n = 50; n > 9; --n) {
		double* X = new double[n + 1]; //vector X[n+1]
		double* U = new double[n + 1]; //vector X[n+1]
		//Grid
		double h = (b0 - a0) / n;
		for (int i = 0; i < n + 1; i++)
		{
			X[i] = a0 + i * h;
			//cout << X[i] << endl;
		}
		//===
		//cout << "h=" << h << endl;
		double* w1 = new double[n + 1];
		double* w2 = new double[n + 1];
		double* w3 = new double[n + 1];

		FillBoard(n, X, h, w1, w2, w3);
		double* F = FillF(X, n, h);

		SolveMatrix(n + 1, w3, w2, w1, F, U);
		free(F);
		WriteResult(U, n + 1, fp);

		//WriteResultA(U, n + 1, "Unew.csv");
		delete[] w1;
		delete[] w2;
		delete[] w3;
		delete[] X;
		delete[] U;
	}
	fclose(fp);

	if ((fp = fopen("outrage.csv", "w")) == NULL)
	{
		printf("Не удалось открыть файл");
		return -1;
	}

	int n = 50;
	double alpha0Init = 2;
	double alpha1Init = -2.5;
	double AInit = 2;
	double beta0Init = 3;
	double beta1Init = 0;
	double BInit = 3 / exp(1);
	for (double delta = 0.0000001; delta <= 0.1; delta *= 10) {
		alpha0 = alpha0Init + delta * alpha0Init;
		alpha1 = alpha1Init + delta * alpha1Init;
		A = AInit + delta * AInit;
		beta0 = beta0Init + delta * beta0Init;
		beta1 = beta1Init + delta * beta1Init;
		B = BInit + delta * BInit;
		double* X = new double[n + 1]; //vector X[n+1]
		double* U = new double[n + 1]; //vector X[n+1]
		//Grid
		double h = (b0 - a0) / n;
		for (int i = 0; i < n + 1; i++)
		{
			X[i] = a0 + i * h;
			//cout << X[i] << endl;
		}
		//===
		//cout << "h=" << h << endl;
		double* w1 = new double[n + 1];
		double* w2 = new double[n + 1];
		double* w3 = new double[n + 1];

		FillBoard(n, X, h, w1, w2, w3);
		double* F = FillF(X, n, h);

		SolveMatrix(n + 1, w3, w2, w1, F, U);
		free(F);
		WriteResult(U, n + 1, fp);

		//WriteResultA(U, n + 1, "Unew.csv");
		delete[] w1;
		delete[] w2;
		delete[] w3;
		delete[] X;
		delete[] U;
	}
//===
//print W
//printf("w1: ");
//for (int i = 0; i < n + 1; i++)
//{
//	printf("%lf ", w1[i]);
//}
//cout << endl;
//printf("w2: ");
//for (int i = 0; i < n + 1; i++)
//{
//	printf("%lf ", w2[i]);
//}
//cout << endl;
//printf("w3: ");
//for (int i = 0; i < n + 1; i++)
//{
//	printf("%lf ", w3[i]);
//}
//cout << endl;
////===
//cout << endl;
////print F
//for (int i = 0; i < n + 1; i++) {
//	cout << "F[" << i << "]=" << F[i] << " ";
//}
//cout << endl;
//cout << endl;
//===
//solve A*X1=B
// тут был solveMatrix
//gauss(W, F, X1, n + 1); //solve
//print X1
//for (int i = 0; i < n + 1; i++)
//{
//	cout << "U[" << i << "]=" << U[i] << " ";
//}
	return 0;
}