#include <iostream>
using namespace std;
const int _size = 4000;

class factorial  {

private:

	int m_array[_size];
    int m_artadryal;
    int m_mnacord = 0; 
    int m_qanak;
    int _m = 1;

public:
	void _factorial(int);
	void _display();
	
};

void factorial::_factorial(int _n) {
    
    while(_m--) {
       m_array[0] = 1;  
       m_qanak = 1;    
        m_mnacord = 0; 
        
        
       for(int i = 1; i <= _n; i++) {
            for(int j = 0; j < m_qanak; j++) {
               m_artadryal = m_array[j] * i + m_mnacord;
               m_array[j] = m_artadryal % 10;
               m_mnacord = m_artadryal / 10;
            }
            
             while(m_mnacord > 0) { 
               m_array[m_qanak] = m_mnacord % 10;
               m_mnacord = m_mnacord / 10;
               m_qanak++;
            }
        }
    }
}

void factorial::_display() {
	for ( int i = m_qanak - 1; i >= 0; i--) {
            cout << m_array[i];
	}
}

int main() {
	int _number;
	factorial _obj;
    cin >> _number;
	
	_obj._factorial(_number);
	_obj._display();
	
	return 0;
}