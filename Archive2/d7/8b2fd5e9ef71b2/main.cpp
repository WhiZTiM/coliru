#include <iostream>
#include <string>
#include <map>
#include <random>
 
// Fitness evaluation 
//Modify fitness in one or both of the following manners
vector<double> evaluation_fitness(vector<double> fitness_vec,vector< vector<int> > P)
{
    int d=0;
	double h=0;
	double sum_h;
	double fitness_raw=0;
	double fitness_new=0;
	vector<double> fitness_vec_adjust;// Store fitness of individuals
	for (int i=0;i<P.size();i++)//for i=1 to N
	{
		sum_h=0;
		fitness_raw=fitness_vec[i];
		for (int j=0;j<P.size();j++)
		{
			d=hamming_dis(P[i],P[j]);
			if(d>=D)
				h=0;
			else
				h=1-(double)d/D;
			//Compute the zeta value
			if(i!=j)
			{
				sum_h=sum_h+h;
			}
		}
		//Modified fitness
		if(sum_h!=0)
		{
			fitness_new=(double)fitness_raw/sum_h;
		}
		else
		{
			fitness_new=fitness_raw;
		}
		
		fitness_vec_adjust.push_back(fitness_new);
		//cout<<"fitness_raw="<<fitness_raw<<endl;
		//cout<<"fitness_new="<<fitness_new<<endl;
		

		
	}

	return fitness_vec_adjust;
}