#include <vector>
#include <iostream>

class MatrixMemory
{
   private:
       std::vector<std::vector<double>> data;

   public:
       void AllocateMemory(int row, int col) {data.resize(row, std::vector<double>(col));}
       MatrixMemory() { }
       int GetRowSize() const
       {
           return data.size();
       }
    
       int GetColumnSize(void) const
       {
           if (!data.empty())
               return 0;
           return data[0].size();
       }
       void SetItem(int row, int col, double value)
       {
           data[row][col] = value; 
       }
       
       double GetItem(int row, int col)
       {
           return data[row][col];
       }
       void Show(void);    
};

using namespace std;

int main()
{
    MatrixMemory m;
    m.AllocateMemory(20, 20);
    m.SetItem(0,0,300);
    double val = m.GetItem(0,0);
    cout << val << "\n";
    
    MatrixMemory m2 = m;
    cout << m2.GetItem(0,0);
}