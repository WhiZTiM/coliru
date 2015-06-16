#include<iostream>

struct Member {};

template <typename T>
class BaseDAO
{
protected:
    virtual void addObject(T)=0;
    virtual void removeObject(T)=0;
    virtual T getObject();
};

class MemberDAO : public BaseDAO<Member>
{
public:
    void addObject(Member) {}
    void removeObject(Member) {}
    Member getObject() {
      std::cout << "getObject()!!!" << std::endl; 
      return Member();
    }
};


int main() {
    MemberDAO foo;
    foo.getObject();
}