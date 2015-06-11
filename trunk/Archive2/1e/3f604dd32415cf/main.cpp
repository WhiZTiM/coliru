#include <stdio.h>
#include <functional>

using namespace std::placeholders;


double getLJForceAtoms (int, int, double*, double*, double*)
{
    printf("getLJForceAtoms\n");
	return 0;
}


double getCoulombForceAtoms (int, int, double*, double*)
{
	printf("getCoulombForceAtoms\n");
	return 0;
}


void getFF (int natom, double* Rs_, std::function<double(int, int, double*)> GetForce)
{
	int rProbe = 1;

	double Force = GetForce(rProbe, natom, Rs_);
}


int main ()
{
	double* C6 = nullptr;
	double* C12 = nullptr;
	double *kQQs = nullptr;
	double* Rs_ = nullptr;

	auto getLJForceFunc = std::bind(getLJForceAtoms, _1, _2, _3, C6, C12);
	auto getCoulombForceFunc = std::bind(getCoulombForceAtoms, _1, _2, _3, kQQs);

	getFF(1, Rs_, getLJForceFunc);
	getFF(1, Rs_, getCoulombForceFunc);
	
	return 0;
}