#include <iostream>
#include <unistd.h> 
#include <future>
#include <random>
#include <vector>
#include <cmath>

using namespace std;


int main()
{
    vector<double> myvector;

	/* Pseudo randomic distribution */
	auto value = std::chrono::system_clock::now().time_since_epoch().count();
	std::default_random_engine generator (value);
	std::uniform_real_distribution<double> distribution(0, 1);	

	for (auto i = 0; i < 10000; ++i) {
		double x = acos(distribution(generator));
		myvector.push_back(x);		
	}

	cout << endl << "первые 100 значений" << endl;
	for (auto i = 0; i < 100; ++i) {
		cout << /*i << "-random value = " << */ myvector[i] << "; ";/* << endl;*/		
	}

	cout << endl << endl << "вариант 10 " << endl; 
	cout <<"f(x) = { cos(x), x принадлежит (-Pi/2; 0)" << endl << "\t 0, иначе" << endl;

	double Mx = -0.9987;
	double Dx = 0.1422;

	cout << endl << "Mx = " << Mx << " Dx = " << Dx << endl;

	double X = 0;
	double S = 0;
	
	for (auto i = 0; i < 10000; ++i) {
		X += myvector[i];		
	}
	X = X /	10000;
	cout << endl << "X=" << X << endl;

	for (auto i = 0; i < 10000; ++i) {
		double temp = (myvector[i] - X) * (myvector[i] - X);
		S += temp;		
	}
	S = S / 10000;
	cout << endl << "S=" << S << endl;

	return 0;
}
