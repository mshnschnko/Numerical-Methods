#pragma warning(disable:4996)
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <windows.h>

double** CreateMatrix(int n, int m)
{
	double** A = NULL;
	int i;
	A = (double**)malloc(n * sizeof(double*));
	if (!A)
		return NULL;
	for (i = 0; i < n; i++)
	{
		A[i] = (double*)malloc(m * sizeof(double));
		if (!A[i])
		{
			int j;
			for (j = 0; j < i; j++)
				free(A[j]);
			return NULL;
		}
	}
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
	for (i = 0; i < n; i++)
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
		for (j = 0; j < m; j++)
		{
			printf("%.3lf ", matrix[i][j]);
		}
		printf("\n");
	}
	printf("\n");
}

void PrintVector(FILE* rootsfileforrec, double* arr, int n)
{
	if (arr == NULL)
		return;
	int i;
	//FILE* rootsThomas = fopen("rootsThomas.csv", "a");
	for (i = 0; i < n; i++)
		fprintf(rootsfileforrec, "%.17lf;", arr[i]);
	fprintf(rootsfileforrec, "\n");
}

double** GetInverseDiagMatrix(double** diagMatrix, int n)
{
	int i, j;
	double** inversedMatrix = NULL;
	inversedMatrix = CreateMatrix(n, n);
	if (!inversedMatrix)
		return NULL;
	for (i = 0; i < n; i++)
		for (j = 0; j < n; j++)
			if (i == j)
				inversedMatrix[i][j] = 1 / diagMatrix[i][j];
			else
				inversedMatrix[i][j] = 0;
	return inversedMatrix;
}

double* MxV(double** M, double* V, int n)
{
	double* x = NULL;
	x = (double*)malloc(n * sizeof(double));
	if (!x)
		return NULL;
	for (int i = 0; i < n; i++) {
		x[i] = 0;
		for (int j = 0; j < n; j++)
			x[i] += M[i][j] * V[j];
	}
	return x;
}

double** MxM(double** A, double** B, int n)
{
	double** C = NULL;;
	C = CreateMatrix(n, n);
	if (!C)
		return NULL;
	for (int i = 0; i < n; i++)
		for (int j = 0; j < n; j++) {
			C[i][j] = 0;
			for (int k = 0; k < n; k++)
				C[i][j] += A[i][k] * B[k][j];
		}
	return C;
}

double* VectorsSum(double* V1, double* V2, int n)
{
	int i;
	double* V = NULL;
	V = (double*)malloc(n * sizeof(double));
	if (!V)
		return NULL;
	for (i = 0; i < n; i++)
		V[i] = V1[i] + V2[i];
	return V;
}

double** DiagMatrix(double** A, int n)
{
	double** D = NULL;
	D = CreateMatrix(n, n);
	if (!D)
		return NULL;
	int i, j;
	for (i = 0; i < n; i++)
		for (j = 0; j < n; j++)
			if (i == j)
				D[i][j] = A[i][j];
			else
				D[i][j] = 0;
	return D;
}

double NormOfMatrix(double** matrix, int n, int m)
{
	int i, j;
	double sum, max = 0;
	for (j = 0; j < m; j++)
	{
		sum = 0;
		for (i = 0; i < n; i++)
			sum += fabs(matrix[i][j]);
		if (sum >= max)
			max = sum;
	}
	return max;
}

double NormVecDif(double* V1, double* V2, int n)
{
	double norm = 0;
	int i;
	for (i = 0; i < n; i++)
		norm += fabs((V1[i] - V2[i]));
	return norm;
}

double* Jacobi(double** matrix, int n, double* average, int* iters)
{
	int i, j;
	double* x = NULL, e = 0.0000000001;
	x = (double*)malloc(n * sizeof(double));
	if (!x)
		return NULL;
	for (i = 0; i < n; i++) //заполнение x0
		x[i] = matrix[i][n] / matrix[i][i];
	double* xNext = NULL;
	xNext = (double*)malloc(n * sizeof(double));
	if (!xNext)
	{
		free(x);
		return NULL;
	}
	double** C = NULL;
	C = CreateMatrix(n, n);
	if (!C)
	{
		free(x);
		free(xNext);
		return NULL;
	}

	for (i = 0; i < n; i++) //заполнение матрицы C
	{
		for (j = 0; j < n; j++)
		{
			if (i == j)
				C[i][j] = 0;
			else
				C[i][j] = (-1) * matrix[i][j] / matrix[i][i];
		}
	}
	//PrintMatrix(C, n, n);
	double* B = NULL; //вектор свободных коэффициентов
	B = (double*)malloc(n * sizeof(double));
	if (!B)
	{
		free(x);
		DestroyMatrix(C, n);
		return NULL;
	}
	for (i = 0; i < n; i++)
		B[i] = matrix[i][n];
	double* g = NULL;
	g = (double*)malloc(n * sizeof(double));
	if (!g)
	{
		free(x);
		DestroyMatrix(C, n);
		free(B);
		return NULL;
	}
	for (i = 0; i < n; i++)
		g[i] = B[i] / matrix[i][i];
	double* CX = NULL;
	CX = MxV(C, x, n);
	if (!CX)
	{
		free(x);
		DestroyMatrix(C, n);
		free(B);
		free(g);
		return NULL;
	}
	for (i = 0; i < n; i++)
		xNext[i] = CX[i] + g[i];
	*iters = 0;
	while (NormVecDif(xNext, x, n) > (1 - NormOfMatrix(C, n, n)) * e / NormOfMatrix(C, n, n))
	{
		free(CX);
		for (i = 0; i < n; i++)
			x[i] = xNext[i];
		CX = MxV(C, xNext, n);
		for (i = 0; i < n; i++)
			xNext[i] = CX[i] + g[i];
		(*iters)++;
	}
	double sum = 0, sumAverage = 0;
	for (i = 0; i < n; i++)
	{
		for (j = 0; j < n; j++)
			if (i != j)
				sum += fabs(matrix[i][j]);
		//printf("%lf ", fabs(matrix[i][i]) / sum);
		sumAverage += fabs(matrix[i][i]) / sum;
		sum = 0;
	}
	*average = sumAverage / n;
	
	//xNext = VectorsSum(MxV(MatrixSum(UnitMatrix(n), OppositeMatrix(MxM(GetInverseDiagMatrix(DiagMatrix(matrix, n), n),
		//matrix, n), n), n), x, n), MxV(GetInverseDiagMatrix(DiagMatrix(matrix, n), n), x, n), n);
	free(x);
	free(B);
	free(g);
	free(CX);
	DestroyMatrix(C, n);
	printf("\n=====\n");
	for (i = 0; i < n; i++)
		printf("%lf", xNext[i]);
	return xNext;
}

int main(void)
{
	const char* matrixAfilename = "matrixA.csv";
	const char* matrixBfilename = "matrixB.csv";
	const char* rootsJacobifilename = "rootsJacobi.csv";
	const char* Nfilename = "N.txt";
	const char* degreefilename = "degree.csv";

	FILE* matrixAfile = fopen(matrixAfilename, "r");
	FILE* matrixBfile = fopen(matrixBfilename, "r");
	FILE* Nfile = fopen(Nfilename, "r");
	FILE* rootsJacobifile = fopen(rootsJacobifilename, "w");
	fclose(rootsJacobifile);
	rootsJacobifile = fopen(rootsJacobifilename, "a");
	FILE* degreefile = fopen(degreefilename, "w");
	fclose(degreefile);
	degreefile = fopen(degreefilename, "a");

	int n, count, *iters = NULL;
	iters = (int*)malloc(sizeof(int));
	if (!iters)
		return -1;
	if (fscanf(Nfile, "%i %i", &n, &count) == 0)
	{
		fclose(matrixAfile);
		fclose(matrixBfile);
		fclose(rootsJacobifile);
		fclose(Nfile);
		return -1;
	}
	fclose(Nfile);
	double** matrix = NULL;
	double* x = NULL, * average = NULL;
	average = (double*)malloc(sizeof(double));
	if (!average)
		return -1;
	int i;
	for (i = 0; i < count; i++)
	{
		matrix = ReadMatrix(matrixAfile, matrixBfile, n);
		if (!matrix)
		{
			printf("ERROR");
			return -1;
		}
		x = Jacobi(matrix, n, average, iters);
		if (!x)
			return -1;
		fprintf(degreefile, "%.17lf; %i\n", *average, *iters);
		PrintVector(rootsJacobifile, x, n);
	}
	
	DestroyMatrix(matrix, n);
	free(x);
	fclose(matrixAfile);
	fclose(matrixBfile);
	fclose(rootsJacobifile);
	
	
	const char* matrixForComparefilename = ("matrixforcompare.csv");
	const char* matrixBForComparefilename = ("matrixBforcompare.csv");
	const char* rootsForComparefilename = ("rootsforcompareJ.csv");
	const char* timefilename = ("time2.csv");

	FILE* matrixForComparefile = fopen(matrixForComparefilename, "r");
	FILE* matrixBForComparefile = fopen(matrixBForComparefilename, "r");
	FILE* rootsForComparefile = fopen(rootsForComparefilename, "w");
	FILE* timefile = fopen(timefilename, "w");
	fclose(timefile);
	timefile = fopen(timefilename, "a");

	printf("\n\n");
	LARGE_INTEGER freq, begin, end;
	double dt, sum = 0;
	for (n = 10; n <= 500; n += 10)
	{
		matrix = ReadMatrix(matrixForComparefile, matrixBForComparefile, n);
		printf("\n===========\n");
		//PrintMatrix(matrix, n, n);
		printf("\n===========\n");
		for (i = 0; i < 20; i++)
		{
			//matrix = ReadMatrix(matrixForComparefile, matrixBForComparefile, n);



			if (!matrix)
			{
				printf("ERROR");
				return 0;
			}
			//PrintMatrix(A, dimensionOfMatrix, dimensionOfMatrix + 1);
			QueryPerformanceFrequency(&freq);
			QueryPerformanceCounter(&begin);
			x = Jacobi(matrix, n, average, iters);
			if (!x)
				return -1;
			//DestroyMatrix(matrix, n);
			QueryPerformanceCounter(&end);
			dt = ((double)((end.QuadPart) - (begin.QuadPart))) / (freq.QuadPart);
			sum += dt;
			//PrintVector(rootsForComparefile, x, n);
		}
		PrintVector(rootsForComparefile, x, n);
		DestroyMatrix(matrix, n);
		dt = sum / 20;
		sum = 0;
		fprintf(timefile, "%i;", n);
		fprintf(timefile, "%.10lf;\n", dt);
	}

	const char* testfilename = ("test.csv");

	FILE* testfile = fopen(testfilename, "r");

	const char* testBfilename = ("testB.csv");

	FILE* testBfile = fopen(testBfilename, "r");

	matrix = ReadMatrix(testfile, testBfile, 3);
	x = Jacobi(matrix, 3, average, iters);

	free(x);
	fclose(matrixForComparefile);
	fclose(matrixBForComparefile);
	fclose(rootsForComparefile);
	fclose(degreefile);

	//PrintVector(rootsJacobifile, Jacobi(matrix, n), n);
	return 0;
}