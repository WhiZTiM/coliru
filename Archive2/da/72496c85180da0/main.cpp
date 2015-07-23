    #include <iostream>

using namespace std;

class vehicle
{
protected:
    string brand;
    int wheelNumber;
    double maxSpeed=0;
public:
    vehicle(){cout<<"default ctor for vehicle"<<endl;}
    vehicle(string br1, int wn1, double ms1)
    {brand=br1; wheelNumber=wn1; maxSpeed=ms1;}

    void setbrand(string br){brand=br;}
    string getbrand(string br){return brand;}
    void setWN(int wn){wheelNumber=wn;}
    int getWN(int wn){return wheelNumber;}
    void setMaxS(double ms){maxSpeed=ms;}
    double getMaxS(double ms){return maxSpeed;}
    ~vehicle(){cout<<"dtor for vehicle."<<endl;}
};
class car: public vehicle
{
private:
    int numberOfDoors;
    string fuelType;
public:
    car(){cout<<"default ctor for car"<<endl;}
    car(int nOD,string fT){numberOfDoors=nOD; fuelType=fT;}

    void setnOD(int nOD){numberOfDoors=nOD;}
    int getnOD(int nOD){return numberOfDoors;}
    void setfT(string fT){fuelType=fT;}
    string getfT(string fT){return fuelType;}

    void printFeatures()
    {
        cout<<endl;
        cout<<"brand:"<<brand<<endl;
        cout<<"wheelNumber:"<<wheelNumber<<endl;
        cout<<"MaxSpeed:"<<maxSpeed<<endl;
        cout<<"NumberOfDoors:"<<numberOfDoors<<endl;
        cout<<"FuelType:"<<fuelType<<endl<<endl;
    }
    ~car(){cout<<"dtor for car."<<endl;}
};

int main()
{
    car *cc;
    cc= new car;
    cc->setbrand("bmw");
    cc->setfT("diesel");
    cc->setMaxS(333.25);
    cc->setWN(4);
    cc->setnOD(6);
    cc->printFeatures();
    delete cc;

    car *xx;
    xx= new car;
    car(5,"gasoline"):vehicle("mercedes",4,489.12);//Part that i cant figure it out.
    xx->printFeatures();
    delete xx;
}