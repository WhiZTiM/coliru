#include <iostream>
using namespace std;
 
class Vektor
{
    public:
            int *P;
            int len;
            int curr_len;
    public:
            Vektor(int s)
            {
                    curr_len = 0;
                    len = s;
                    P = new int[len];
            }
            Vektor(const Vektor &v)
        	{	
    			P = new int(v.len);
    			
    			curr_len = v.curr_len;
    			len = v.len;
    			for (int i = 0; i < curr_len-1; i++)
    				P[i] = v.P[i];
    		}

            bool append(int);
           
            ~Vektor(){ delete[] P; }
};
 
bool Vektor::append(int a)
{
    if (curr_len + 1 > len || P == NULL)
    {
            cout << "Nije definirana velicina vektora" << endl;
            return false;
    }
    P[curr_len] = a;
    curr_len++;
    return true;
}
 
int main(void)
{
    Vektor v(5);

    v.append(3);

    Vektor z(v);

    return 0;
}