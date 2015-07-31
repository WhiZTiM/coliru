template <typename Param>
struct X
{
  template <typename T> void foo () { }   
};

template <typename Param>
struct Y : X<Param>
{
    void thing ()
    {
        this->template foo<int> ();
    }
};

int main ()
{
}