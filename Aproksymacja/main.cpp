#include <iostream>
using namespace std;

void countLeftArray(double *tabX, double **&leftArray, int size, int amountOfPoints);
void countRightrray(double *tabX, double *tabY, double *&rightArray, int size, int amountOfPoints);
void createTriangleArray(double **leftArray, double *rightArray, int size, double **&triangleArray);
void countFactors(double *&factorsArray, double **triangleArray, int size);

int main()
{
	int size = 4;
	double **leftArray = new double *[size];
	for (int i = 0; i < size; i++)
		leftArray[i] = new double[size];

	double **triangleArray = new double *[size];
	for (int i = 0; i < size; i++)
		triangleArray[i] = new double[size + 1];

	double *factorsArray = new double[size];
	double *rightArray = new double[size];


	double tabX[] = { -5, -4, -3, -2, -1, 0, 1, 2, 3, 5 };
	double tabY[] = { -110, -60, -20, -10, -1.5, 2, 7, 18, 50, 170 };
	int amountOfPoints = 10;

	//countLeftArray(tabX, leftArray, size, amountOfPoints);
	//countRightrray(tabX, tabY, rightArray, size, amountOfPoints);

	leftArray[0][0] = 4;
	leftArray[0][1] = -2;
	leftArray[0][2] = 4;
	leftArray[0][3] = -2;
	leftArray[1][0] = 3;
	leftArray[1][1] = 1;
	leftArray[1][2] = 4;
	leftArray[1][3] = 2;
	leftArray[2][0] = 2;
	leftArray[2][1] = 4;
	leftArray[2][2] = 2;
	leftArray[2][3] = 1;
	leftArray[3][0] = 2;
	leftArray[3][1] = -2;
	leftArray[3][2] = 4;
	leftArray[3][3] = 2;

	rightArray[0] = 8;
	rightArray[1] = 7;
	rightArray[2] = 10;
	rightArray[3] = 2;
	createTriangleArray(leftArray, rightArray, size, triangleArray);
	countFactors(factorsArray, triangleArray, size);

	for (int i = 0; i < size; i++)
		cout << "Factor " << i << ": " << factorsArray[i] << endl;

	for (int i = 0; i < size; i++)
		delete[] leftArray[i];

	delete[] leftArray;

	for (int i = 0; i < size; i++)
		delete[] triangleArray[i];

	delete[] triangleArray;

	delete[] factorsArray;
	delete[] rightArray;

	system("PAUSE");
	return 0;
}

void countLeftArray(double *tabX, double **&leftArray, int size, int amountOfPoints)
{
	for (int i = 0; i < size; i++)
		for (int k = 0; k < size; k++)
		{
			double tmp = 0;

			for (int j = 0; j < amountOfPoints; j++)
				tmp += pow(tabX[j], i + k);

			leftArray[i][k] = tmp;
		}
}

void countRightrray(double *tabX, double *tabY, double *&rightArray, int size, int amountOfPoints)
{
	for (int k = 0; k < size; k++) 
	{
		double tmp = 0;

		for (int j = 0; j < amountOfPoints; j++)
			tmp += tabY[j] * pow(tabX[j], k);
		
		rightArray[k] = tmp;
	}
}

void createTriangleArray(double **leftArray, double *rightArray, int size, double **&triangleArray)
{
	for (int i = 0; i < size; i++)
		for (int j = 0; j < size; j++)
			triangleArray[i][j] = leftArray[i][j];

	for (int i = 0; i < size; i++)
		triangleArray[i][size] = rightArray[i];

	for (int k = 0; k < size; k++)
	{
		double denominator = triangleArray[k][k];
		if (denominator == 0)
			denominator = 1e-12;

		double rightArrayMultiplier = triangleArray[k][size];

		for (int i = (k + 1); i < size; i++)
		{
			double counter = triangleArray[i][k];
			
			for (int j = k; j < (size + 1); j++)
			{
				if (j != size)
					triangleArray[i][j] -= (counter / denominator) * triangleArray[k][j];

				else
					triangleArray[i][j] -= (counter / denominator) * rightArrayMultiplier;
			}
		}
	}
}

void countFactors(double *&factorsArray, double **triangleArray, int size)
{
	factorsArray[size - 1] = triangleArray[size - 1][size] / triangleArray[size - 1][size - 1];
	
	for (int i = (size - 2); i > -1; i--)
	{
		double tmpValue = 0;
		double denominator = triangleArray[i][i];

		for (int j = (size - 1); j > i; j--)
			tmpValue += triangleArray[i][j] * factorsArray[j];
		

		factorsArray[i] = (triangleArray[i][size] - tmpValue) / denominator;
	}
}