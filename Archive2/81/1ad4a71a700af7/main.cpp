#include <iostream>

class VectorInt
{
public:
    explicit VectorInt(int i)
    {
        i_tam = i;
        p_vec = new int[i_tam];
        
        for (int idx = 0; idx < i_tam; ++idx)
            p_vec[idx] = 0;
    }
    
    int tam() const { return i_tam; }
    
    int at(int idx) const
    { return p_vec[idx]; }
    
    int& at(int idx)
    { return p_vec[idx]; }
    
private:
    int i_tam;
    int* p_vec;
};

void print(const VectorInt& v)
{   
    v.at(1) = 4;
    
    for (int idx = 0; idx < v.tam(); ++idx)
        std::cout << v.at(idx) << " ";
    
    std::cout << std::endl;
}

int main()
{
    VectorInt v(5);
    
    v.at(3) = 5;
    
    print(v);
        
    for (int idx = 0; idx < v.tam(); ++idx)
        v.at(idx) = idx;

    print(v);
    
    return 0;
}
