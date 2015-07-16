#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;
const int _size = 4000;

class factorial  {

private:

    int m_factorial;
	int m_array[_size];
    int artadryal;
    int mnacord = 0;       

public:
	void _factorial(int);
	void _display();
	
};

void factorial::_factorial(int _n){
     int k = 3999;
    m_array[3999] = 1;
	
    for(int i = 2; i <= _n; i++){
        while(k > 0){
            artadryal = m_array[k] * i + mnacord;
            mnacord = 0;
            
            if(artadryal > 9){
                m_array[k] = artadryal % 10;
                mnacord = artadryal / 10;
            } 
            else{
            m_array[k] = artadryal;}
            k--;
        }
        
        mnacord = 0;
        artadryal = 0;
        k = 3999;
    }
}

void factorial::_display(){
	for ( int i = 0; i < _size; i++) {
            cout << m_array[i];
	}
}

int main() {
	int _number = 1000;
	factorial _obj;
	//cin >> _number;
	
	_obj._factorial(_number);
	_obj._display();
	
	return 0;
}