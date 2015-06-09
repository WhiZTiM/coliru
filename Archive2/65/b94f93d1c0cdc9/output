#include <iostream>
#include <assert.h>
using namespace std;
template<typename TArrayItem, int Size>
class myarray
{
private:
   TArrayItem items[Size];  //Statically allocated array.
public:
   myarray(intializer_list<TArray>values)
   {
      int i = 0;
      for (TArrayItem value : values) //Range-For(C++/11)
      {
         items[i++] = value;
      }
   }
   inline int size() const inline
   {
      return Size;
   }

   TArrayItem operator[](/* my array *this */ int index)
   {
      //assertion
      assert(index  < Size, "Index out of range");
      return items[index];
   }
};

int main()
{
   myarray<int, 5> arr = {1,2,3,4,5};
   cout << arr.size() << endl;
   cout << arr[0] << endl;

   //arr.operator[](0);
   // myarray<int,5> :: operator[] (&arr,0);
   // Limker : jmp 1000(&arr,0)
   return 0;
}