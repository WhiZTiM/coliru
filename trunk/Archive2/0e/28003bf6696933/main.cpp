#include<vector>
#include<string>
#include<iostream>


using namespace std;

 struct myStruct 
{
        uint32_t content1;
        uint32_t content2;
        uint32_t content3;
        uint32_t content4;
};
    
class myClass
    {
        public:
            void Update();
            void Retrieve(std::vector<myStruct> &list);
            void Retrieve();
        private:
            std::vector<myStruct> m_list;
    };
    void myClass::Update()
    {
        myStruct temp;

       temp.content1=2;
       temp.content2=3;
        m_list.push_back(temp);
    }

 //void myClass::Retrieve( std::vector<myStruct> &list)
   
    void myClass::Retrieve( )
    {
        //for(uint32_t i=0; i<m_list.size(); i++)
         for ( auto &x : m_list)
            std::cout << x.content1 << std::endl;
               // list = m_list;
    }
    void myClass::Retrieve( std::vector<myStruct> &list)
    {
        for(uint32_t i=0; i<m_list.size(); i++)
            std::cout << m_list[i].content1 << std::endl;
                list = m_list;
    }
    
int main(){
 myClass me;
 me.Update();
 me.Retrieve();
 std::vector<myStruct> list;
 me.Retrieve(list);
    
}
