template<typename Itr, typename SizeT = int> inline Itr next(Itr it, SizeT /*n*/ = 1)
{ return it; }

int main()
{
    int i = 0;
    next(i);
}