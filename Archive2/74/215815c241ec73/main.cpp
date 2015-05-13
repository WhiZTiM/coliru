    template <class DataType>
class Checkbook
{
public:
    Checkbook( );
    DataType getLastCheck( ) const;
    Checkbook( float iBalance );
    bool writeCheck( const DataType & amount );
    void setBalance( float amnt );
    void deposit( float amount );
    float getBalance(  ) const;
    float getLastDeposit( ) const;
private:
    float balance;
    DataType lastCheck;
    float lastDeposit;
};
#include<iostream>
using namespace std;
template <class DataType>
bool operator > (DataType tempcheck, float z)
{
    if (tempcheck.amount > z)
        return true;
    return false;
}

template <class DataType>
float operator - (float z, DataType tempcheck)
{
    z = z - tempcheck.amount;
    return z;
}
///////////////////////////////////////////

template <class DataType>
Checkbook<DataType>::Checkbook( ){}

template <class DataType>
Checkbook<DataType>::Checkbook( float initBalance )
{balance = initBalance;}

template <class DataType>
void Checkbook<DataType>::setBalance( float amount )
{balance = amount;}

template <class DataType>
bool Checkbook<DataType>::writeCheck( const DataType & amount )
{
    if ( amount > balance )
        return false;
    balance = balance - amount;
    cout<<"\n\nbalance = "<<balance<<endl<<endl;
    lastCheck = amount;
    return true;
}

template <class DataType>
void Checkbook<DataType>::deposit( float amount )
{
    balance += amount;
    lastDeposit = amount;
}

template <class DataType>
float Checkbook<DataType>::getBalance( ) const
{
    return balance;
}

template <class DataType>
DataType Checkbook<DataType>::getLastCheck( ) const
{
    return lastCheck;
}

template <class DataType>
float Checkbook<DataType>::getLastDeposit( ) const
{
    return lastDeposit;
}

#include <iterator>
#include <vector>//include vector
#include <iostream>
#include <iomanip>
#include <ctime>
#include <string>
#include <sstream>


using namespace std;

struct Check

{
    static string Name;
    static string account;
    int check;
    string checkDate;
    float amount;
    string comment;
    string receipent;
};

string Check::Name = "";
string Check::account = "";

int main( )

{

    std::forward_list<Check> lck(ck.begin(), ck.end());
    //std::vector<Check> ck(100);
    float balance;
    float Deposit=0.0;

    time_t now = time(0);
    tm *ltm = localtime(&now);

    string CurrentDate;
    stringstream mon, day, year;
    int temp;

    temp = 1 + ltm->tm_mon;
    mon << temp;


    temp = ltm->tm_mday;
    day << temp;


    temp = 1900 + ltm->tm_year;
    year << temp;
    CurrentDate = mon.str() + "/" + day.str() + "/" + year.str();


    cout<<"\nEnter name of Account Holder : ";

    getline(cin,Check::Name);
    cout<<"\nEnter Account No : ";

    getline(cin,Check::account);
    cout <<"\nEnter your initial balance: ";

    cin >> balance;
    Check tempCk;
        Checkbook<Check> cbook( balance );
    int i=0;
    int j;
    int choice=0;

    do
        {
        cout<<endl<<"\n1- Writing checks";
        cout<<endl<<"\n2- Show last checks";
        cout<<endl<<"\n3- Deposit";
        cout<<endl<<"\n4- Show Balance";
        cout<<endl<<"\n5- Quit";

        cout<<"\n\nEnter your choice : ";
        cin>>choice;

        switch(choice)

        {
            case 1:
                cout<<"\nCheck Number : "<<i+1<<endl;
                ck[i].check = i+1;
                cout<<"\nEnter receipent name : ";
                cin>> ck[i].receipent;
                cout<<"\nEnter amount : ";

                cin>>ck[i].amount;
                cout<<"\nDate of check : "<<CurrentDate<<endl;
                ck[i].checkDate = CurrentDate;
                cout<<"\nEnter Comment for check : ";

                getline(cin,ck[i].comment);

                               if(!cbook.writeCheck(ck[i]))                   {
                 cout<<"\n\nNot enough balance "<<ck[i].amount<<endl<<endl;
         }
                 else
                 i++;
                 break;

            case 2:
                cout<<"\n\nDetails of Last Check\n\n";
                for(j = i-1;j>=0;j--)

                {
                    cout<<"\nCheck Number : "<<ck[j].check;
                    cout<<"\nDate of Check : "<<ck[j].checkDate;
                    cout<<"\nReceipent : "<<ck[j].receipent;
                    cout<<"\nAmount on Check : "<<ck[j].amount;
                    cout<<"\nComment : "<<ck[j].comment;
                }

                break;

            case 3:
                cout<<"\nEnter amount to deposit : ";
                cin>>Deposit;
                cbook.deposit(Deposit);
                break;

            case 4:
                cout << fixed << showpoint << setprecision( 3 );
                cout << "Current Balance is: " << cbook.getBalance( )<<" " << endl;
                break;

            default:
                if(choice!=5)
                    cout<<"\n\nInvalid Entry, please try again\n";
        } }
        while(choice!=5);
    return 0;
}