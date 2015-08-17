//Current case
class Up : public UpParent
{
    void f1();
    void f2();
    void f3();
    int m1;
    int m2;
    int m3;
    UpParent getParent();
};

class Down : public DownParent
{
    void f1();
    void f2();
    void f3();
    int m1;
    int m2;
    int m3;
    DownParent getParent();
};

template <typename Parent>
class AnywayYouLike : public Parent
{
    void f1();
    void f2();
    void f3();
    int m1;
    int m2;
    int m3;
    Parent getParent();
};

typedef AnywayYouLike<UpParent> Up;
typedef AnywayYouLike<DownParent> Down;



