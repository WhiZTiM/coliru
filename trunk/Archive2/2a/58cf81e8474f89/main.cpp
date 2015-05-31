#include <vector>

class NonCopyable
{
public:
    NonCopyable(const NonCopyable&) = delete;
    NonCopyable& operator=(const NonCopyable&) = delete;


protected:
    NonCopyable()
    {
    }

    ~NonCopyable() 
    {
    }
};


class Member : NonCopyable
{
public:
    Member(int i) : mNum(i)
    {
    }
    ~Member()
    {
    }

    Member(Member&& other)  : mNum(other.mNum)
    {
    }

    Member& operator= (Member&& other)
    {
        std::swap(mNum, other.mNum);
        return *this;
    }

private:
    int mNum;
};


struct Item
{
    Item(int i) : mMember(i)
    {
    }

    Member mMember;
};



int main(int argc,char **argv)
{
    std::vector<Item> vec;
    vec.emplace_back(1);

    return 0;
}