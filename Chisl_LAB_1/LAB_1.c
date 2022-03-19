#include <stdio.h>
#include <stdlib.h>
#define _USE_MATH_DEFINES
#include <math.h>
#pragma warning(disable: 4996)

typedef struct
{
	double value;
	int count;
}root;

double FuncAlg(double x)
{
	return (2 * pow(x, 5) + 3 * pow(x, 4) - 4 * pow(x, 3) - 12 * x * x + 10);
}

double FuncTrans(double x)
{
	return (pow(5, x) - sin(x) - 3);
}

double FuncTest(double x)
{
	return (x * x + x - 6);
}

double df(double x, double (*f)(double))
{
	double dfc, h = 0.000001;
	dfc = (f(x + h) - f(x - h)) / (2 * h);
	return dfc;
}

double d2f(double x, double (*f)(double))
{
	double df2, h = 0.000001;
	df2 = (f(x + h) - 2 * f(x) + f(x - h)) / (h * h);
	return df2;
}

root Bisection(double a, double b, double e, double (*f)(double), const char* filename, const char* filenameones)
{
	double c;
	root x;
	x.count = 0;
	FILE* file = fopen(filename, "a");
	FILE* fileones = NULL;
	if (e == 0.0000001)
		fileones = fopen(filenameones, "w");
	//fprintf(file, "k;[a, b];f(a);f(b);f(c);c\n");
	while (fabs(b - a) > 2 * e)
	{
		c = (a + b) / 2;
		if (f(a) * f(c) < 0)
			b = c;
		else
			a = c;
		x.count++;
		//fprintf(file, "%i;%lf;%lf\n", x.count, (a + b) / 2, e);
		if (e == 0.0000001)
			fprintf(fileones, "%i;%.15lf;%.15lf\n", x.count, (a + b) / 2, e);
	}
	x.value = (a + b) / 2;
	fprintf(file, "%i;%.15lf;%.15lf\n", x.count, x.value, e);
	fclose(file);
	return x;
}

root ChordNewton(double a, double b, double e, double (*f)(double), const char* filename, const char* filenameones)
{
	//double xn1, xp1 = b, tmp1, xn2, xp2 = a, tmp2;
	root x;
	x.count = 0;
	FILE* file = fopen(filename, "a");
	FILE* fileones = NULL;
	if (e == 0.0000001)
		fileones = fopen(filenameones, "w");

	while (fabs(a - b) > 2 * e)
	{
		if (f(a) * d2f(a, f) < 0)
			a = a - f(a) * (a - b) / (f(a) - f(b));
		else if (f(a) * d2f(a, f) > 0)
			a = a - f(a) / df(a, f);
		if (f(b) * d2f(b, f) < 0)
			b - f(b) * (b - a) / (f(b) - f(a));
		else if (f(b) * d2f(b, f) > 0)
			b = b - f(b) / df(b, f);
		x.count++;
		if (e == 0.0000001)
			fprintf(fileones, "%i;%.15lf;%.15lf\n", x.count, (a + b) / 2, e);
		//fprintf(fileones, "%i;%.15lf;%.15lf\n", x.count, (a + b) / 2, e);
	}
	x.value = (a + b) / 2;
	fprintf(file, "%i;%.15lf;%.15lf\n", x.count, x.value, e);
	fclose(file);
	return x;
}

int main(void)
{
	double a, b, e = pow(10, -10);
	root xhd1, xnew1, xhd2, xnew2, xx1, xx2;
	while (e != 0.01)
	{
		a = 1.3;
		b = 3.0;
		xhd1 = Bisection(a, b, e, &FuncAlg, "BisAlg.csv", "BisAlgOnes.csv");
		xnew1 = ChordNewton(a, b, e, &FuncAlg, "ComboAlg.csv", "ComboAlgOnes.csv");

		a = 0.8;
		b = 2.0;
		xhd2 = Bisection(a, b, e, &FuncTrans, "BisTrans.csv", "BisTransOnes.csv");
		xnew2 = ChordNewton(a, b, e, &FuncTrans, "ComboTrans.csv", "ComboTransOnes.csv");
		e *= 10;
	}
	e = 0.0000001;
	double delta = 0;
	root xBisUdAlg, xBisUdTrans, xComboUdAlg, xComboUdTrans;
	FILE* Udal = fopen("Udal.csv", "a");
	while (delta != 30)
	{
		a = 1.3;
		b = 3.0 + delta;
		xBisUdAlg = Bisection(a, b, e, &FuncAlg, "BisUdAlg.csv", "BisUdAlgOnes.csv");
		xComboUdAlg = ChordNewton(a, b, e, &FuncAlg, "ComboUdAlg.csv", "ComboUdAlgOnes.csv");
		

		a = 0.8;
		b = 2.0 + delta;
		xBisUdTrans = Bisection(a, b, e, &FuncTrans, "BisUdTrans.csv", "BisUdTransOnes.csv");
		xComboUdTrans = ChordNewton(a, b, e, &FuncTrans, "ComboUdTrans.csv", "ComboUdTransOnes.csv");

		fprintf(Udal, "%lf;%i;%i;%i;%i\n", delta, xBisUdAlg.count, xBisUdTrans.count, xComboUdAlg.count, xComboUdTrans.count);
		delta += 3;
	}
	return 0;
}