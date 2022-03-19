#pragma warning(disable:4996)
#include <stdio.h>
#include <math.h>
#include <windows.h>

double** CreateMatrix(int n, int m)
{
	double** A = NULL;
	int i;
	A = (double**)malloc(n * sizeof(double*));
	for ( i = 0; i < n; i++)
		A[i] = (double*)malloc(m * sizeof(double));
	return A;
}

void DestroyMatrix(double** A, int n)
{
	int i;
	for (i = 0; i < n; i++)
		free(A[i]);
	free(A);
}

double** ReadMatrix(FILE* matrixfile, FILE* freekoeffile, int n)
{
	//printf("%i", n);
	double** matrix = CreateMatrix(n, n + 1);
	//double** freekoef = CreateMatrix(n, 1);
	int i, j;
	for  (i = 0; i < n; i++)
		for (j = 0; j < n; j++)
			if (fscanf(matrixfile, "%lf;", &matrix[i][j]) != 0)
				if (fabs(round(10000000000 * matrix[i][j])) == 0)
					matrix[i][j] = 0;
	for (i = 0; i < n; i++)
		fscanf(freekoeffile, "%lf;", &matrix[i][n]);
	double** ret = NULL;
	return matrix;
}

void PrintMatrix(double** matrix, int n, int m)
{
	int i, j;
	for (i = 0; i < n; i++)
	{
		for (j = 0; j < n + 1; j++)
		{
			printf("%.3lf ", matrix[i][j]);
		}
		printf("\n");
	}
	printf("\n");
}

void PrintVector(FILE* rootsfileforrec, double* arr, int n)
{
	int i;
	//FILE* rootsThomas = fopen("rootsThomas.csv", "a");
	for (i = 0; i < n; i++)
		fprintf(rootsfileforrec, "%.17lf;", arr[i]);
	fprintf(rootsfileforrec, "\n");
}

double* Thomas(double** matrix, int n)
{
	int count = -1;
	double timemeas = -1;
	int i;
	double* b = NULL;
	b = (double*)malloc(n * sizeof(double));
	if (b == NULL)
		return NULL;
	b[0] = 0;
	double* d = NULL;
	d = (double*)malloc(n * sizeof(double));
	if (d == NULL)
		return NULL;
	d[n - 1] = 0;
	double* c = NULL;
	c = (double*)malloc(n * sizeof(double));
	if (c == NULL)
		return NULL;
	for (i = 0; i < n; i++)
	{
		c[i] = matrix[i][i];
		if (i != n - 1)
			d[i] = matrix[i][i + 1];
		if (i != 0)
			b[i] = matrix[i][i - 1];
	}
	double* delta = NULL;
	delta = (double*)malloc(n * sizeof(double));
	if (delta == NULL)
		return NULL;
	double* lambda = NULL;
	lambda = (double*)malloc(n * sizeof(double));
	if (lambda == NULL)
		return NULL;
	delta[0] = -d[0] / c[0];
	lambda[0] = matrix[0][n] / c[0];
	for (i = 1; i < n; i++)
	{
		delta[i] = -d[i] / (b[i] * delta[i - 1] + c[i]);
		lambda[i] = (matrix[i][n] - b[i] * lambda[i - 1]) / (b[i] * delta[i - 1] + c[i]);
	}
	double* x = NULL;
	x = (double*)malloc(n * sizeof(double));
	if (x == NULL)
		return NULL;
	x[n - 1] = lambda[n - 1];
	for (i = n - 2; i >= 0; i--)
		x[i] = delta[i] * x[i + 1] + lambda[i];
	free(b);
	free(c);
	free(d);
	free(delta);
	free(lambda);
	return x;
}

double* ThomasForTime(double** matrix, int n, FILE* time)
{
	LARGE_INTEGER freq, begin, end;
	double dt;
	int count = -1;
	double timemeas = -1;
	QueryPerformanceFrequency(&freq);
	QueryPerformanceCounter(&begin);
	int i;
	double* b = NULL;
	b = (double*)malloc(n * sizeof(double));
	if (b == NULL)
		return NULL;
	b[0] = 0;
	double* d = NULL;
	d = (double*)malloc(n * sizeof(double));
	if (d == NULL)
		return NULL;
	d[n - 1] = 0;
	double* c = NULL;
	c = (double*)malloc(n * sizeof(double));
	if (c == NULL)
		return NULL;
	for (i = 0; i < n; i++)
	{
		c[i] = matrix[i][i];
		if (i != n - 1)
			d[i] = matrix[i][i + 1];
		if (i != 0)
			b[i] = matrix[i][i - 1];
	}
	double* delta = NULL;
	delta = (double*)malloc(n * sizeof(double));
	if (delta == NULL)
		return NULL;
	double* lambda = NULL;
	lambda = (double*)malloc(n * sizeof(double));
	if (lambda == NULL)
		return NULL;
	delta[0] = -d[0] / c[0];
	lambda[0] = matrix[0][n] / c[0];
	for (i = 1; i < n; i++)
	{
		delta[i] = -d[i] / (b[i] * delta[i - 1] + c[i]);
		lambda[i] = (matrix[i][n] - b[i] * lambda[i - 1]) / (b[i] * delta[i - 1] + c[i]);
	}
	double* x = NULL;
	x = (double*)malloc(n * sizeof(double));
	if (x == NULL)
		return NULL;
	x[n - 1] = lambda[n - 1];
	for (i = n - 2; i >= 0; i--)
		x[i] = delta[i] * x[i + 1] + lambda[i];
	QueryPerformanceCounter(&end);
	dt = ((double)((end.QuadPart) - (begin.QuadPart))) / (freq.QuadPart);
	fprintf(time, "%i;", n);
	fprintf(time, "%.10lf;\n", dt);
	free(b);
	free(c);
	free(d);
	free(delta);
	free(lambda);
	return x;
}

int main(void)
{
	const char* matrixfilename = "csvmatrix.csv";
	const char* freekoeffilename = "freekoef.csv";
	const char* NNNfilename = "NNN.txt";
	const char* rootsThomasfilename = "rootsThomas.csv";

	int i, dimensionOfMatrix, countOfMatrix, deltaLen;

	FILE* matrixfile = fopen(matrixfilename, "r");
	FILE* freekoeffile = fopen(freekoeffilename, "r");
	FILE* NNNfile = fopen(NNNfilename, "r");

	if (fscanf(NNNfile, "%i %i %i", &dimensionOfMatrix, &countOfMatrix, &deltaLen) == 0)
		return -1;

	FILE* rootsThomasfile = fopen(rootsThomasfilename, "w");
	fclose(rootsThomasfile);
	rootsThomasfile = fopen(rootsThomasfilename, "a");

	for (i = 0; i < countOfMatrix; i++)
	{
		double** A = ReadMatrix(matrixfile, freekoeffile, dimensionOfMatrix);
		//PrintMatrix(A, dimensionOfMatrix, dimensionOfMatrix + 1);
		PrintVector(rootsThomasfile, Thomas(A, dimensionOfMatrix), dimensionOfMatrix);
		DestroyMatrix(A, dimensionOfMatrix);
	}

	const char* outrageAfilename = "outrageA.csv";
	const char* outrageBfilename = "outrageB.csv";
	const char* rootsThomasOutragefilename = "rootsThomasOutrage.csv";

	FILE* OutrageAfile = fopen(outrageAfilename, "r");
	FILE* OutrageBfile = fopen(outrageBfilename, "r");
	FILE* rootsThomasOutragefile = fopen(rootsThomasOutragefilename, "w");
	fclose(rootsThomasOutragefile);
	rootsThomasOutragefile = fopen(rootsThomasOutragefilename, "a");

	for (i = 0; i < deltaLen; i++)
	{
		double** A = ReadMatrix(OutrageAfile, OutrageBfile, dimensionOfMatrix);
		//PrintMatrix(A, dimensionOfMatrix, dimensionOfMatrix + 1);
		PrintVector(rootsThomasOutragefile, Thomas(A, dimensionOfMatrix), dimensionOfMatrix);
		DestroyMatrix(A, dimensionOfMatrix);
	}

	const char* matrixForTimefilename = "matrixForTime.csv";
	const char* freekoefForTimefilename = "freekoefForTime.csv";
	const char* rootsThomasForTimefilename = "rootsThomasForTime.csv";
	const char* timefilename = "time.csv";

	FILE* matrixForTimefile = fopen(matrixForTimefilename, "r");
	FILE* freekoefForTimefile = fopen(freekoefForTimefilename, "r");
	FILE* rootsThomasForTimefile = fopen(rootsThomasForTimefilename, "w");
	fclose(rootsThomasForTimefile);
	rootsThomasForTimefile = fopen(rootsThomasForTimefilename, "a");
	FILE* timefile = fopen(timefilename, "w");
	fclose(timefile);
	timefile = fopen(timefilename, "a");
	int n;
	double* x = NULL;
	LARGE_INTEGER freq, begin, end;
	double dt, sum = 0;
	for (n = 10; n <= 500; n += 10)
	{
		double** A = ReadMatrix(matrixForTimefile, freekoefForTimefile, n);
		for (i = 0; i < 1000; i++)
		{
			//double** A = ReadMatrix(matrixForTimefile, freekoefForTimefile, n);
			//PrintMatrix(A, dimensionOfMatrix, dimensionOfMatrix + 1);
			QueryPerformanceFrequency(&freq);
			QueryPerformanceCounter(&begin);
			x = Thomas(A, n);
			QueryPerformanceCounter(&end);
			dt = ((double)((end.QuadPart) - (begin.QuadPart))) / (freq.QuadPart);
			sum += dt;
			//PrintVector(rootsThomasForTimefile, x, n);
			//DestroyMatrix(A, n);
		}
		PrintVector(rootsThomasForTimefile, x, n);
		DestroyMatrix(A, n);
		dt = sum / 1000;
		//sum = 0;
		fprintf(timefile, "%i;", n);
		fprintf(timefile, "%.10lf;\n", dt);
	}

	fclose(OutrageAfile);
	fclose(OutrageBfile);
	fclose(matrixfile);
	fclose(freekoeffile);
	fclose(NNNfile);
	fclose(timefile);
	fclose(matrixForTimefile);
	fclose(freekoefForTimefile);
	fclose(rootsThomasForTimefile);

	const char* matrixForComparefilename = ("matrixforcompare.csv");
	const char* matrixBForComparefilename = ("matrixBforcompare.csv");
	const char* rootsForComparefilename = ("rootsforcompare.csv");

	FILE* matrixForComparefile = fopen(matrixForComparefilename, "r");
	FILE* matrixBForComparefile = fopen(matrixBForComparefilename, "r");
	FILE* rootsForComparefile = fopen(rootsForComparefilename, "w");

	double** A = ReadMatrix(matrixForComparefile, matrixBForComparefile, dimensionOfMatrix);
	PrintMatrix(A, dimensionOfMatrix, dimensionOfMatrix);
	QueryPerformanceFrequency(&freq);
	QueryPerformanceCounter(&begin);
	x = Thomas(A, dimensionOfMatrix);
	QueryPerformanceCounter(&end);
	dt = ((double)((end.QuadPart) - (begin.QuadPart))) / (freq.QuadPart);
	printf("%lf", dt);
	PrintVector(rootsForComparefile, x, dimensionOfMatrix);
	DestroyMatrix(A, dimensionOfMatrix);

	fclose(matrixForComparefile);
	fclose(matrixBForComparefile);
	fclose(rootsForComparefile);

	return 0;
}