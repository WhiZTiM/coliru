#include <list>
#include <iostream>
#include <vector>
using namespace std;


template <typename T, class Allocator> // note: no default allocator
class Queue
{
     Allocator myAllocator;
    
 public:
        void enqueue(T item) 
        {
            myAllocator.push(item);
        }

        T dequeue()
        {
            auto poppedELement = myAllocator.pop();
            return poppedELement;
        }

       // other operations.        
       auto begin() -> decltype(myAllocator.begin()) { return myAllocator.begin(); }
       auto end()   -> decltype(myAllocator.end())   { return myAllocator.end(); }

};



template <class T, template <typename ...> class Container, class ... Args>
class BasicAllocator
{
      Container<T, Args...> M_list;
public:     
      void push(T element)
      {
          M_list.push_back(element);
      }
      T pop()
      { 
         return M_list.front();
      } 
      auto begin() -> decltype( std::begin(M_list) )
      { return std::begin(M_list); }

      auto end()   -> decltype( std::end(M_list) )
      { return std::end(M_list); }
};
template<class T>
using LinkedListAllocator = BasicAllocator<T, std::list>;

template<class T>
using LinkedListQueue = Queue<T, LinkedListAllocator<T>>;
 

template <typename T, typename S>
void testQueue(Queue<T, S> l)
{
l.enqueue(5);  // ints are assumed for simplicity
l.enqueue(51);
l.enqueue(511);
l.enqueue(5111);

 for (auto i : l)
      cout << i << endl;
     
}
    
int main()
{
    LinkedListQueue<int> l;

    testQueue(l);
    
    
}
