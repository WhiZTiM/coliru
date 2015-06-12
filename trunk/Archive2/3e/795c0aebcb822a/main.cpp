#include<vector>
#include<iostream>

    struct reference_helper
    {
        reference_helper(double &_d) : d(_d) {}
        reference_helper& operator=(double rhs)
        {
            if(rhs<0.0)
            {
                std::cout<<"throw exception"<<std::endl;
            }
            else
            {
                std::cout<<"ok"<<std::endl;
                d = rhs;
            }
            return *this;
        }

        operator double& ()
        {
            if(d<0.0)
            {
                std::cout<<"throw exception"<<std::endl;
            }
            return d;
        }

        // add further required functions
    private:
        double& d;
    };


    struct Prediction
    {
         operator double& () { return d; }
         double d = -1.0;
    };

    struct Security
    {
        template<typename ... Args>
        Security(Args&& ... args) : v(std::forward<Args>(args) ...) {}

         auto operator[](int i)
         {
             return reference_helper(v[i]);
         }
        std::vector<Prediction> v;
    };
    
    int main()
    {
        Security s(10);   

        double a = s[0]; //should throw an exception, because predArray[0] = -1
        s[0] = 4; //should be O.K. because I want to change the value
        s[1] = -4;

        return 0;
    }