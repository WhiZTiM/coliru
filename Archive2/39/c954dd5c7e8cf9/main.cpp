#include<iostream>
#include<fstream>
#include<string>
#include <cstdlib>
#include <vector>

using namespace std;
template <class T>

class MatrixViaVector{

public:
    MatrixViaVector();
    MatrixViaVector(int m,int n);
    template <class H>
    friend ostream& operator <<(ostream& outs, const MatrixViaVector<H> &obj);
private:
    int m,n;
    vector<vector<T>> matrix;
};



 template <class T>
    MatrixViaVector<T>::MatrixViaVector(){

        //creates a 3 by 3 matrix with elements equal to 0


        for (int i=0;i<3;i++){
            vector<int> row;
            for (int j=0;j<3;j++)
                row.push_back(0);
            matrix.push_back(row);
        }
    }

template <class T>
MatrixViaVector<T>::MatrixViaVector(int m,int n)//creates a m by n matrix????
{
    //creates a matrix with dimensions m and n with elements equal to 0

    for (int i=0;i<m;i++){
        vector<int> row;
        for (int j=0;j<n;j++)
            row.push_back(0);
        matrix.push_back(row);
    }
}

    template <class T>
    ostream& operator <<(ostream& outs, const MatrixViaVector<T> & obj)
    {
        //obj shud have the vector and therefore I should be able to use its size

       for (std::vector<int>::size_type i = 0; i < obj.matrix.size(); i++){
        for (std::vector<int>::size_type j = 0; j < obj.matrix.size(); j++)
            outs << " "<< obj.matrix[i][j];
        outs<<endl;
    }
        outs<<endl;
        return outs;
    }

    int main()
    {

    MatrixViaVector <int> A;
    MatrixViaVector <int> Az(3,2);//created an object with dimensions 3by2????
    cout<<A<<endl;
    cout<<Az<<endl;//this prints out a 3 by 3 matrix which i dont get????????
    }

