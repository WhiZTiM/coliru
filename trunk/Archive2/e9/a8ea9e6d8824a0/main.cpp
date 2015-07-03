#include <string.h>
#include <algorithm>
#include <iostream>


struct list
{
    char data;
    list * next;
    
};


class MyCircleList
{
    public:
        MyCircleList(const char * src); 
        virtual ~MyCircleList();
        void addElement(const char chr);
        char getNextElement();
        bool isTail() const;
        const int getSize() { return m_size; }
    private:
        list * m_data;
        list * head;
        list * tail;
        int m_size;
};

MyCircleList::MyCircleList(const char * src)
{
    if ( src == NULL)
    {
//        throw std::runtime_eror("Bad pointer");   
    }
    else
    {
        int i = 0;
        m_data = new list;
        head = m_data;
        m_data->data = src[i];
        while (src[++i] != '\0')
        {
            addElement(src[i]);
        }
    }
}

MyCircleList::~MyCircleList()
{
    list *tmp;
    while(m_data != tail)
    {
        tmp = m_data;
        m_data = m_data-> next;
        delete tmp;
    }
    delete tail;
}

char MyCircleList::getNextElement() 
{
    char tmp = m_data->data;
    m_data = m_data->next;
    return tmp;
    
}

void MyCircleList::addElement(const char chr)
{
    m_data->next = new list;
    m_data = m_data->next;
    m_data->data = chr;
    tail = m_data;
    m_data->next = head;
}

bool MyCircleList::isTail() const
{
    return m_data == tail ? true : false;
}

bool isCorrect(const char * first, const char * secondStr)
{
    //MyCircleList firsList(first);
    MyCircleList second(second);
    int i = 0;
    int count = 0;
    bool isCorrect = false;
    while( first[i] != '\0' && count < second.getSize())
    {
        if (!isCorrect)
        {
            while( (first [i] != second.getNextElement()) && (!second.isTail()) );  
            ++count;
        }
        
        if(first [i] != second.getNextElement())
        {
            isCorrect = false;
            break;
        }
        
        isCorrect = true;
    }
    return isCorrect;
}

int main()
{
  char * str1 = new char[5];
  strcpy(str1,"ABCD");
  char * str2 = new char[5];
  strcpy(str2,"CDAB");
 if ( isCorrect(str1, str2) )
  {
      std::cout<<"strings are simillar";
  } 

}
