#pragma warning(disable: 4996)

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <Windows.h>

double g_phi;
int g_i0 = 0;
int g_j0 = 0;
double** G;
int errorG = 0;
double e;

double** CreateMatrix(int n, int m)
{
	double** A = NULL;
	int i;
	A = (double**)malloc(n * sizeof(double*));
	if (A == NULL)
		return NULL;
	for (i = 0; i < n; i++)
	{
		A[i] = (double*)malloc(m * sizeof(double));
		if (A[i] == NULL)
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

double** ReadMatrix(FILE* matrixfile, int n)
{
	double** matrix = NULL;
	matrix = CreateMatrix(n, n);
	if (!matrix)
		return NULL;
	int i, j;
	for (i = 0; i < n; i++)
		for (j = 0; j < n; j++)
			if (fscanf(matrixfile, "%lf;", &matrix[i][j]) != 0)
				if (fabs(round(10000000000 * matrix[i][j])) == 0)
					matrix[i][j] = 0;
	return matrix;
}

void PrintEigenValues(double** matrix, int n)
{
	int i;
	for (i = 0; i < n; i++)
		printf("%lf ", matrix[i][i]);
}

void PrintMatrix(double** matrix, int n, int m)
{
	int i, j;
	for (i = 0; i < n; i++)
	{
		for (j = 0; j < m; j++)
		{
			printf("%.6lf ", matrix[i][j]);
		}
		printf("\n");
	}
	printf("\n");
}

double Frobenius(double** matrix, int n)
{
	int i, j;
	double sum = 0;
	for (i = 0; i < n; i++)
		for (j = 0; j < n; j++)
			sum += matrix[i][j] * matrix[i][j];
	return (sqrt(sum));
}

void ChoosingTheOptimalElement(double** matrix, int n)
{
	int i, j;
	double r = 0, maxr = 0, maxa = 0;
	for (i = 0; i < n; i++)
	{
		r = 0;
		for (j = 0; j < n; j++)
			if (j != i)
				r += matrix[i][j] * matrix[i][j];
		if (r >= maxr)
		{
			maxr = r;
			g_i0 = i;
		}
	}
	for (j = 0; j < n; j++)
		if (fabs(matrix[g_i0][j]) >= maxa && j != g_i0)
		{
			maxa = fabs(matrix[g_i0][j]);
			g_j0 = j;
		}
	return;
}

double getg_phi(double** matrix)
{
	double tg2g_phi = 0;
	tg2g_phi = 2.0 * matrix[g_i0][g_j0] / (matrix[g_i0][g_i0] - matrix[g_j0][g_j0]);
	return (atan(tg2g_phi) / 2);
}

double** TAT(double** matrix, int n)
{
	int k, l;
	double** B = NULL;
	B = CreateMatrix(n, n);
	if (!B)
	{
		DestroyMatrix(matrix, n);
		return NULL;
	}
	for (k = 0; k < n; k++)
		for (l = 0; l < n; l++)
		{
			if (l != g_i0 && l != g_j0)
				B[k][l] = matrix[k][l];
			if (l == g_i0)
				B[k][l] = matrix[k][g_i0] * cos(g_phi) + matrix[k][g_j0] * sin(g_phi);
			if (l == g_j0)
				B[k][l] = (-1) * matrix[k][g_i0] * sin(g_phi) + matrix[k][g_j0] * cos(g_phi);
		}
	for (k = 0; k < n; k++)
		for (l = 0; l < n; l++)
			matrix[k][l] = B[k][l];
	//PrintMatrix(matrix, n, n);
	for (k = 0; k < n; k++)
		for (l = 0; l < n; l++)
		{
			if (l != g_i0 && l != g_j0)
				B[k][l] = matrix[k][l];
			if (k == g_i0)
				B[k][l] = matrix[g_i0][l] * cos(g_phi) + matrix[g_j0][l] * sin(g_phi);
			if (k == g_j0)
				B[k][l] = -matrix[g_i0][l] * sin(g_phi) + matrix[g_j0][l] * cos(g_phi);
		}
	for (k = 0; k < n; k++)
		for (l = 0; l < n; l++)
			matrix[k][l] = B[k][l];
	DestroyMatrix(B, n);
	//PrintMatrix(matrix, n, n);
	return matrix;
}

double StopCondition(double** matrix, int n)
{
	int i, j;
	double sum = 0;
	for (i = 0; i < n; i++)
		for (j = i + 1; j < n; j++)
			//if (i != j) // && fabs(matrix[i][j]) >= max)
			sum += 2 * matrix[i][j] * matrix[i][j];
						//max = fabs(matrix[i][j]);
	if (sum > e)
		return 0;
	else
		return 1;
}

void GetSeparability(double** matrix, FILE* separabilityFile, int n, int iters)
{
	//double separability = 0;
	//int i;
	//for (i = 0; i < n - 1; i++)
	//	separability += fabs(matrix[i + 1][i + 1] / matrix[i][i]);
	//separability /= n - 1.0;
	//fprintf(separabilityFile, "%.10lf;%i\n", separability, iters);
	fprintf(separabilityFile, "%.17lf;%i\n", e, iters);
	return;
}

void GetEigenValues(double** matrix, int n, FILE* EigenValues)
{
	int i;
	for (i = 0; i < n; i++)
		fprintf(EigenValues, "%.17lf;", matrix[i][i]);
	fprintf(EigenValues, "\n");
}

void GetEigenVector(int n, FILE* EigenVectors)
{
	int i, j;
	for (i = 0; i < n; i++)
	{
		for (j = 0; j < n; j++)
		{
			if (i == j)
			{
				if((i == g_i0 && j == g_i0) || (i == g_j0 && j == g_j0))
					fprintf(EigenVectors, "%.17lf;", cos(g_phi));
				else
					fprintf(EigenVectors, "%.17lf;", 1.0);
			}
			else
			{
				if (i == g_j0 && j == g_i0)
					fprintf(EigenVectors, "%.17lf;", sin(g_phi));
				else
				{
					if(i == g_i0 && j == g_j0)
						fprintf(EigenVectors, "%.17lf;", -sin(g_phi));
					else
						fprintf(EigenVectors, "%.17lf;", 0.0);
				}
			}
			//if (i == j && i != g_i0 && i != g_j0 && i != g_j0 && j != g_j0)
			//{
			//	fprintf(EigenVectors, "%.17lf;", 1.0);
			//	continue;
			//}
			//if ((i == g_i0 && j == g_i0) || (i == g_j0 && j == g_j0))
			//{
			//	fprintf(EigenVectors, "%.17lf;", cos(g_phi));
			//	continue;
			//}
			//if (i == g_j0 && j == g_i0)
			//{
			//	fprintf(EigenVectors, "%.17lf;", sin(g_phi));
			//	continue;
			//}
			//if (i == g_i0 && j == g_j0)
			//{
			//	fprintf(EigenVectors, "%.17lf;", -sin(g_phi));
			//	continue;
			//}
			//if (i != j && i != g_i0 && i != g_j0 && j != g_i0 && j != g_j0)
			//{
			//	fprintf(EigenVectors, "%.17lf;", 0.0);
			//	continue;
			//}
		}
		fprintf(EigenVectors, "\n");
	}
	fprintf(EigenVectors, "\n");
}

void PrintEigenVectrors(int n, FILE* eigenVectorsFile)
{
	int i, j;
	for (i = 0; i < n; i++)
	{
		for (j = 0; j < n; j++)
		{
			fprintf(eigenVectorsFile, "%.17lf;", G[i][j]);
		}
		fprintf(eigenVectorsFile, "\n");
	}
	fprintf(eigenVectorsFile, "\n");
}

void FirstG(int n)
{
	int i, j;
	for (i = 0; i < n; i++)
	{
		for (j = 0; j < n; j++)
		{
			if (i == j)
			{
				if ((i == g_i0 && j == g_i0) || (i == g_j0 && j == g_j0))
					G[i][j] = cos(g_phi);
				else
					G[i][j] = 1.0;
			}
			else
			{
				if (i == g_j0 && j == g_i0)
					G[i][j] = sin(g_phi);
				else
				{
					if (i == g_i0 && j == g_j0)
						G[i][j] = -sin(g_phi);
					else
						G[i][j] = 0.0;
				}
			}
		}
	}
}

void NextG(int n)
{
	int k, l;
	double** B = NULL;
	B = CreateMatrix(n, n);
	if (!B)
	{
		errorG = 1;
		return;
	}
	for (k = 0; k < n; k++)
		for (l = 0; l < n; l++)
		{
			if (l != g_i0 && l != g_j0)
				B[k][l] = G[k][l];
			if (l == g_i0)
				B[k][l] = G[k][g_i0] * cos(g_phi) + G[k][g_j0] * sin(g_phi);
			if (l == g_j0)
				B[k][l] = (-1) * G[k][g_i0] * sin(g_phi) + G[k][g_j0] * cos(g_phi);
		}
	for (k = 0; k < n; k++)
		for (l = 0; l < n; l++)
			G[k][l] = B[k][l];
	DestroyMatrix(B, n);
}

double** Jacobi(double** matrix, int n, int* iters)
{
	*iters = 0;
	//int * g_i0 = NULL, * g_j0 = NULL;
	//g_i0 = (int*)malloc(sizeof(int));
	//if (!g_i0)
	//	return NULL;
	//g_j0 = (int*)malloc(sizeof(int));
	//if (!g_j0)
	//{
	//	free(g_i0);
	//	return NULL;
	//}
	while (!StopCondition(matrix, n))
	{
		ChoosingTheOptimalElement(matrix, n);
		g_phi = getg_phi(matrix);
		matrix = TAT(matrix, n);
		if (!matrix)
			return NULL;
		if (*iters == 0)
			FirstG(n);
		if (*iters > 0)
			NextG(n);
		if (errorG == 1)
			return NULL;
		//PrintMatrix(matrix, n, n);
		(*iters)++;
	}
	////PrintMatrix(matrix, n, n);
	//free(g_i0);
	//free(g_j0);
	////PrintMatrix(matrix, n, n);
	return matrix;
}

int main(void)
{
	const char* matrixFileName = "matrix.csv";
	const char* Nfilename = "N.txt";
	const char* separabilityfilename = "separability.csv";
	const char* eigenValuesFileName = "EigenValues.csv";
	const char* timeEigenFileName = "timeEigen.csv";

	FILE* matrixFile = fopen(matrixFileName, "r");
	FILE* Nfile = fopen(Nfilename, "r");
	FILE* separabilityfile = fopen(separabilityfilename, "w");
	FILE* eigenValuesFile = fopen(eigenValuesFileName, "w");
	FILE* timeEigenFile = fopen(timeEigenFileName, "w");
	fclose(eigenValuesFile);
	eigenValuesFile = fopen(eigenValuesFileName, "a");

	int n, count, i, j;

	if (fscanf(Nfile, "%i %i", &n, &count) == 0)
	{
		fclose(matrixFile);
		fclose(Nfile);
		fclose(separabilityfile);
		fclose(eigenValuesFile);
		fclose(timeEigenFile);
		return -1;
	}

	fclose(Nfile);
	int* iters = NULL;
	iters = (int*)malloc(sizeof(int));
	if (!iters)
	{
		fclose(matrixFile);
		fclose(separabilityfile);
		fclose(eigenValuesFile);
		fclose(timeEigenFile);
		return -1;
	}
	double** matrix = NULL;
	G = CreateMatrix(n, n);
	if (!G)
	{
		fclose(matrixFile);
		fclose(separabilityfile);
		fclose(eigenValuesFile);
		fclose(timeEigenFile);
		free(iters);
		return -1;
	}
	matrix = ReadMatrix(matrixFile, n);
	if (!matrix)
	{
		DestroyMatrix(G, n);
		fclose(matrixFile);
		fclose(separabilityfile);
		fclose(eigenValuesFile);
		fclose(timeEigenFile);
		free(iters);
		return -1;
	}
	double** matrix1 = CreateMatrix(n, n);
	if (!matrix1)
	{
		DestroyMatrix(G, n);
		DestroyMatrix(matrix, n);
		fclose(matrixFile);
		fclose(separabilityfile);
		fclose(eigenValuesFile);
		fclose(timeEigenFile);
		free(iters);
		return -1;
	}
	//for (i = 0; i < n; i++)
	//	for (j = 0; j < n; j++)
	//		matrix1[i][j] = matrix[i][j];
	for (e = 0.000000000000001; e < 0.001; e *= 10)
	{
		//matrix = ReadMatrix(matrixFile, n);
		//if (!matrix)
		//	return -1;
		//PrintMatrix(matrix, n, n);
		for (i = 0; i < n; i++)
			for (j = 0; j < n; j++)
				matrix1[i][j] = matrix[i][j];
		matrix1 = Jacobi(matrix1, n, iters);
		PrintMatrix(matrix, n, n);
		if (!matrix)
			return -1;
		//GetEigenValues(matrix, n, eigenValuesFile);
		GetSeparability(matrix1, separabilityfile, n, *iters);
		//PrintMatrix(matrix, n, n);
		//DestroyMatrix(matrix1, n);
	}
	matrix = ReadMatrix(matrixFile, n);
	if (!matrix)
	{
		DestroyMatrix(G, n);
		fclose(matrixFile);
		fclose(separabilityfile);
		fclose(eigenValuesFile);
		fclose(timeEigenFile);
		free(iters);
		return -1;
	}
	for (e = 0.000000000000001; e < 0.001; e *= 10)
	{
		//matrix = ReadMatrix(matrixFile, n);
		//if (!matrix)
		//	return -1;
		//PrintMatrix(matrix, n, n);
		for (i = 0; i < n; i++)
			for (j = 0; j < n; j++)
				matrix1[i][j] = matrix[i][j];
		matrix1 = Jacobi(matrix1, n, iters);
		if (!matrix)
			return -1;
		//GetEigenValues(matrix, n, eigenValuesFile);
		GetSeparability(matrix1, separabilityfile, n, *iters);
		//PrintMatrix(matrix, n, n);
		//DestroyMatrix(matrix1, n);
	}
	fclose(separabilityfile);
	//fclose(eigenValuesFile);
	fclose(matrixFile);

	const char* outrageFileName = "Outrage.csv";
	FILE* outrageFile = fopen(outrageFileName, "r");
	const char* eigenVectorsFileName = "EigenVectors.csv";
	FILE* eigenVectorsFile = fopen(eigenVectorsFileName, "w");

	for (i = 0; i < 6; i++)
	{
		matrix = ReadMatrix(outrageFile, n);
		if (!matrix)
			return -1;
		G = CreateMatrix(n, n);
		//PrintMatrix(matrix, n, n);
		matrix = Jacobi(matrix, n, iters);
		GetEigenValues(matrix, n, eigenValuesFile);
		//GetEigenVector(n, eigenVectorsFile);

		//GetSeparability(matrix, separabilityfile, n, *iters);
		//PrintMatrix(matrix, n, n);
		PrintEigenVectrors(n, eigenVectorsFile);
		DestroyMatrix(matrix, n);
	}
	DestroyMatrix(G, n);
	fclose(eigenValuesFile);
	fclose(outrageFile);
	fclose(eigenVectorsFile);

	//const char* matrixTimeFileName = "matrixTime.csv";
	//FILE* matrixTimeFile = fopen(matrixTimeFileName, "r");

	//LARGE_INTEGER freq, begin, end;
	//double dt, sum = 0;
	//int dimension, k, l;
	//double** matrix1 = NULL;
	//printf("==");
	//for (dimension = 10; dimension < 100; dimension += 5)
	//{
	//	matrix = ReadMatrix(matrixTimeFile, dimension);
	//	if (!matrix)
	//		return -1;
	//	/*matrix1 = CreateMatrix(dimension, dimension);
	//	if (!matrix1)
	//		return -1;*/
	//	//PrintMatrix(matrix, n, n);
	//	for (j = 0; j < 10; j++)
	//	{
	//		//for (k = 0; k < dimension; k++)
	//		//	for (l = 0; l < dimension; l++)
	//		//		matrix1[k][l] = matrix[k][l];
	//		QueryPerformanceFrequency(&freq);
	//		QueryPerformanceCounter(&begin);
	//		matrix = Jacobi(matrix, dimension, iters);
	//		QueryPerformanceCounter(&end);
	//		dt = ((double)((end.QuadPart) - (begin.QuadPart))) / (freq.QuadPart);
	//		sum += dt;
	//	}

	//	//GetEigenValues(matrix, dimension, eigenValuesFile);
	//	//GetSeparability(matrix, separabilityfile, dimension, *iters);
	//	DestroyMatrix(matrix, dimension);
	//	//DestroyMatrix(matrix1, dimension);
	//	dt = sum / 20;
	//	sum = 0;
	//	fprintf(timeEigenFile, "%i;", dimension);
	//	fprintf(timeEigenFile, "%lf;\n", dt);
	//}

	//fclose(timeEigenFile);
	free(iters);
	//matrix = ReadMatrix(matrixFile, n);
	//fclose(matrixFile);
	//if (!matrix)
	//	return -1;
	//PrintMatrix(matrix, n, n);
	//matrix = Jacobi(matrix, n);
	//if (!matrix)
	//	return -1;
	//PrintEigenValues(matrix, n);
	//DestroyMatrix(matrix, n);
	return 0;
}