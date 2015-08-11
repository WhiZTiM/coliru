//C++ program to calculate volume and surface area
// v1.1 pyramids

#include <iostream>
#include <math.h>
using namespace std;

double cyl_vol(double r, double h, double pi)
{
    pi = 4*atan(1);
	double Vcylinder = (pi * pow(r,2) * h);
	return Vcylinder;
}


int main(){

	double r; //radius
	double h; //perpendicular height
	double l; //length
	double s; //length of slant
	//double b; base *not yet implemented*
	double pi = 4 * atan(1);

 
	//Volume + Total Surface Area (Hemisphere)
	string hemi1 = "1";
	string hemi2 = "2";
	double Vhemisphere = ((2/3) * pi * pow(r,3));
	double TSAhemisphere = (3 * pi * pow(r,2));

	//Volume + Total Surface Area (Cylinder)
	string cyl1 = "3";
	string cyl2 = "4";
	double Vcylinder = (pi * pow(r,2) * h);
	double TSAcylinder = ((2 * pi * pow(r,2)) + (2 * pi * r * h));

	//Volume + Total Surface Area (Cone)
	string cone1 = "5";
	string cone2 = "6";
	double Vcone = ((1/3) * pi * pow(r,2) * h);
	double TSAcone = ((pi * pow(r,2)) + (pi * r * s));

	bool x = (hemi1 == hemi2);
	bool y = (cyl1 == cyl2);
	bool z = (cone1 == cone2);

	cout << "Welcome to Volume/Surface Area calculator!\n \n -=-MENU-=-\n1) Volume Hemisphere\n2) Suface Area Hemisphere\n";	
	cin >> x ;
	if(x){c
		//double cyl_vol;
		//double Vhemisphere = ((2/3) * pi * pow(r,3));
	    //double TSAhemisphere = (3 * pi * pow(r,2));
		cout << "Enter radius: ";
		cin >> r;
		cout << "Volume of Hemisphere: " << Vcylinder<< "\n";
		cout << "Surface Area of Hemisphere: "<< TSAhemisphere << "\n";
	}
	/*else if(y){
		cout << "Enter radius: \n";
		cin >> r;
		cout << "Enter height: \n";
		cout << "Volume of Cylinder: " << Vcylinder << "\n";

	}
	*/

	return 0;	
}
