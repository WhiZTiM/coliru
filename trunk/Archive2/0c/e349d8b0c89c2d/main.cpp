//Title of this code
//Rextester.Program.Main is the entry point for your code. Don't change it.
//Compiler version 4.0.30319.17929 for Microsoft (R) .NET Framework 4.5

#include <iostream>
#include <vector>
#include <numeric>
#include <algorithm>
#include <iterator>

using namespace std;

class LinkedList
{
    
    private:
      struct Node
      {
          int m_data;
          Node* m_next;
          
          Node(int data) : m_data(data), m_next(nullptr) { }
      };
      
      
    public:
        
        void Add(int data)
        {
            if (m_head == nullptr)
            {
                m_head = new Node(data);
            }
            else
            {
                Node* temp = new Node(data);
                
                Node* currNode = m_head;
                while(currNode->m_next != nullptr) currNode = currNode->m_next;
                currNode->m_next = temp;                
            }
        }
        
        void DeleteDuplicates()
        {          
            Node* currNode = m_head;            
            Node* currNext = nullptr;
            Node* startOfDuplicates = nullptr;
            Node* endOfDuplicates = nullptr;
            Node* prevUniqueNode = nullptr;
            
            bool duplicatesFound = false;
            
            auto DeleteDuplicates = [&]
            {                        
                if (m_head == startOfDuplicates) 
                {
                    // need to change the head.
                    m_head = endOfDuplicates->m_next;                                    
                }
                else
                {
                    prevUniqueNode->m_next = endOfDuplicates->m_next;
                }
                
                Node* temp = startOfDuplicates;
                while(temp != m_head)
                {
                    Node* tempNext = temp->m_next;
                    delete temp;
                    temp = tempNext;
                }
                
                std::cout << "deleted duplicates\n";
            };
            
            
            for (; currNode != nullptr;)
            {                
                currNext = currNode->m_next;
                
                if (currNext == nullptr) break;
                                
                if (!duplicatesFound && currNode->m_data == currNext->m_data)
                {
                    startOfDuplicates = currNode;
                    duplicatesFound = true;
                }
                else if (duplicatesFound && currNode->m_data != currNext->m_data)
                {
                    endOfDuplicates = currNode;                    
                    DeleteDuplicates();
                    duplicatesFound = false;
                    startOfDuplicates = endOfDuplicates = nullptr;
                }                
                else
                {
                    prevUniqueNode = currNode;
                }
                currNode = currNode->m_next;
                
            }        
            
            
                        
        }
        
        void Print()
        {
                Node* currNode = m_head;
                while(currNode->m_next != nullptr)
                {
                    std::cout << currNode->m_data << "=>";
                    currNode = currNode->m_next;
                }
                std::cout << currNode->m_data;
        }
        
        
    private:
        Node* m_head = nullptr;
};

template<typename T, size_t SZ>
size_t SIZE(const T(&)[SZ])
{
    return SZ;
}


template<typename Iter, typename T>
Iter FindMinHelper(Iter start, Iter finish, T t)
{
    int mid = std::distance(start, finish) / 2;
    
    auto pos = std::next(start, mid);
    if (*pos < *std::prev(pos))
    {
        return pos;
    }
    else
    {
        return FindMinHelper(pos, finish, t);
    }
}


template<typename Iter, typename T>
Iter FindMin(Iter start, Iter finish, T t)
{
    if (std::distance(start, finish) == 1)
    {
        return *start == t ? start : finish;
    }
    
    if ((*std::next(start) > *start))
    {
        return start;
    }
    
    return FindMinHelper(start, finish, t);
}



int main()
{
    /*std::vector<int> data { 2, 5, 10, 4, 1 };
    
    int max_diff = -1;
    
    
    
    for (int i = 0; i < data.size(); ++i)
    {
        for (int j = i + 1; j < data.size(); ++j)
        {
            if (data[j] > data[i] &&  max_diff < (data[j] - data[i]))
            {
                max_diff = data[j] - data[i];
            }
        }
    }
    
    
    std::cout << max_diff << '\n';
    
    */
    
 /*   LinkedList l;
    l.Add(1);
    l.Add(2);
    l.Add(3);
    l.Add(3);
    l.Add(4);
    l.Add(4);
    l.Add(5);
    
    
    
    l.DeleteDuplicates();
    l.Print();
    
   */
   
   
   int arr[] = { 1,4,5,6,2 };
   
   std::sort(arr, arr + SIZE(arr));
   std::rotate(std::rbegin(arr), std::rbegin(arr) +1, std::rend(arr));
   
   for(auto e : arr)
   {
       std::cout << e << '\n';
   }
    
   std::cout << "find element in rotated sorted array\n";
   
    
    auto pos = FindMin(arr, std::end(arr), 10);
    
    if (pos != std::end(arr))
    {
        std::cout << *pos << '\n';
    }
    
}