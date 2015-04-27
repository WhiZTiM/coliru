#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <complex.h> 


#define Ix 401
#define J 5
//#define 
#define pi 3.14159265359
#define EP0 8.85418e-12
#define MU0 4.0e-7 * pi


int main(void)
{

    int i = 0;

	FILE *fp;

	fp = fopen("testcc.txt", "r");

	double Matrix[Ix][J];
	double EM[Ix][5];

	double DIST = 0.98e-3;

	//double ETA0 = sqrt(MU0 / EP0);

	double C = 2.99792458e8; 
	double OMEG, temp1;
	
	double complex GAMMA = 1.0 + 1.0 * I;
	double complex temp;
    double complex Z;
    double complex S11;
    double complex S21;
    double complex K;
    double complex T;
    double complex X;
    double complex Y = 0;
Z= 1.0 + 1.0 * I;
	for (i = 0; i < Ix; ++i)
	{
		for (int j = 0; j < J; ++j)
		{
			fscanf(fp, "%lf", &Matrix[i][j]);
		}
	}

	for (i = 0; i < Ix; ++i)
	{

		OMEG = 2 * pi*Matrix[i][1] * 1e9;


		S11 = Matrix[i][1] + I * Matrix[i][2];
		S21 = Matrix[i][3] + I * Matrix[i][4];


		K = ((cpow(S11,2) - cpow(S21,2)) + 1) / (2 * S11);

		GAMMA = K + csqrt(K*K - 1);

		T = ((S21 + S11) - GAMMA) / (1 - (S11 + S21)*GAMMA);


		//X = ((1 + GAMMA) / (1 - GAMMA)) ^ 2;
		X = cpow(((1 + GAMMA) / (1 - GAMMA)), 2);
		//Y = -(C / (OMEG*DIST)*clog(1 / T)) ^ 2;
		//Y = -cpow((C / (OMEG*DIST)*clog(1 / T)), 2
		temp = clog(1 / T);
		temp1 = C/(OMEG*DIST);
		temp = temp*temp1;
		temp = cpow(temp, 2);
		temp = -temp;

		Z = X*Y;


		EM[i][1] = creal(csqrt(Y / X));
		EM[i][2] = cimag(csqrt(Y / X));
		EM[i][3] = creal(Y / EM[i][1]);
		EM[i][4] = cimag(Y / EM[i][1]);

	}




	//for (int i = 0; i < I; ++i)
	//{
	//	for (int j = 0; j < J; ++j)
	//	{
	//		printf("%lf  ", Matrix[i][j]);
	//	}
	//	printf("\n");
	//}







	return 0;
}
