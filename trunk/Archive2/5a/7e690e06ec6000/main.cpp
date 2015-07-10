#include <iostream>
using namespace std;
class Teacher{
    public:
        int age;
        Teacher(int a):age(a){}
    friend ostream& operator<<(ostream& out, const Teacher& t)
    {
        out << t.age;
        return out;
    }
};
int main()
{
    Teacher t(1);
    cout << t <<　endl;
    return 0;
}