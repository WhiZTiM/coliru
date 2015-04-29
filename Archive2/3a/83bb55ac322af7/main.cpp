#include <iostream>
using namespace std;


void Print(double **a, int N){
    for (int i = 0; i < N; i++){
		for (int j = 0; j < N + 1; j++){
			cout.precision(2);
			cout.width(4);
			cout << a[i][j] << " ";
		}
		cout << endl;
	}
	cout << endl;
}



double JordanGauss(double **a, int N){

	int s1 = 0, e1 = N, s2 = 0, e2 = N + 1;
	double k;
	int flag = N - 1;
	
	while (flag > 0){
		k = a[s1][s2];
		#pragma omp parallel for
			for (int j = s2; j < e2; j++){
				if (k != 0) a[s1][j] = a[s1][j] / k;
			}
		++s1;
		#pragma omp parallel for
			for (int i = s1; i < e1; i++) {
				k = a[i][s2];
				for (int j = s2; j < e2; j++){
					a[i][j] = a[i][j] - k * a[s1 - 1][j];
				}
			}
		++s2;
		--flag;
	}

	k = a[s1][s2];
	#pragma omp parallel for
		for (int j = s2; j < e2; j++){
			if (k != 0) a[s1][j] = a[s1][j] / k;
		}

	cout << "First step:\n";
	Print(a, N);

	s1 = 0;
	s2 = N - 1;
	e1 = N - 1;
	flag = N - 1;
	while (flag > 0){
		#pragma omp parallel for
			for (int i = s1; i < e1; i++){
				k = a[i][s2];
				for (int j = s1; j < e2; j++){
					a[i][j] = a[i][j] - k * a[s2][j];
				}
			}
		--e1;
		--s2;
		--flag;
	}

	return **a;
}




int main() {
	bool flag = true;
	int sw;
	int N;

//	while (flag){
		cout << "0 - Exit\n";
		cout << "1 - 2x2 matrix\n";
		cout << "2 - 3x3 matrix\n";
		cout << "3 - manual input\n";
		cin >> sw;

		switch (sw)
		{			
			case 0:{
				flag = false;
				break;
			}

			case 1:{
				N = 2;
				double **a = new double *[N];
				for (int i = 0; i < N; i++){
					a[i] = new double[N + 1];
				}
				a[0][0] = 1;
				a[0][1] = 4;
				a[0][2] = 3;
				a[1][0] = 3;
				a[1][1] = 5;
				a[1][2] = 2;

				//system("cls");
				cout << "Matrix:\n";
				Print(a, N);

				JordanGauss(a, N);
				cout << "Result:\n";
				Print(a, N);
				break;
			}

			case 2:{
				N = 3;
				double **a = new double *[N];
				for (int i = 0; i < N; i++){
					a[i] = new double[N + 1];
				}
				a[0][0] = 1;
				a[0][1] = 1;
				a[0][2] = 1;
				a[0][3] = 0;
				a[1][0] = 4;
				a[1][1] = 2;
				a[1][2] = 1;
				a[1][3] = 1;
				a[2][0] = 9;
				a[2][1] = 3;
				a[2][2] = 1;
				a[2][3] = 3;

			//	system("cls");
				cout << "Matrix:\n";
				Print(a, N);

				JordanGauss(a, N);
				cout << "Result:\n";
				Print(a, N);
				break;
			}

			case 3:{
				cout << "Input size of matrix: ";
				cin >> N;
				double **a = new double *[N];
				for (int i = 0; i < N; i++){
					a[i] = new double[N + 1];
				}
				// identity matrix
				for (int i = 0; i < N; i++){
					for (int j = 0; j < N + 1; j++){						
						//a[i][j] = rand() %9;
							a[i][j] = 0;
					}
				}
				
				//system("cls");
				cout << "Matrix:\n";
				Print(a, N);
				
				JordanGauss(a, N);
				cout << "Result:\n";
				Print(a, N);

				for (int i = 0; i < N; i++) 
					delete [] a[i];
				delete [] a;
				break;
			}

		default:
			break;
		}
//	}
	return 0;
}