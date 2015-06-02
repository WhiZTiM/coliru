
#include <iostream>
using namespace std;

class Date {

public:
    
    //Constructors
    Date() : m_day(0), m_month(0), m_year(0){}
    Date(const int &d, const int &m, const int &y) : m_day(d), m_month(m), m_year(y){}
    ~Date(){}
    
	void displayDate() const {
        cout << m_month << "/" << m_day << "/" << m_year;
    }
	
    bool lessThan(const Date &d) const {
        
        if (m_year < d.m_year) {
            return true;
	    }
	    if(m_year == d.m_year && m_month < d.m_month) {
		    return true;
	    }
	    if(m_year == d.m_year && m_month < d.m_month && m_day < d.m_day) {
		    return true;
	    }
	    return false;
    }
	

protected:
	int m_day;
	int m_month;
	int m_year;
};

bool operator< (const Date &d1, const Date &d2) {
    return d1.lessThan(d2);
}

int main() {
    Date d1(2,3,0);
    Date d2(4,6,8);
    bool b = d1<d2;
    cout << b << endl;
    return 0;
}