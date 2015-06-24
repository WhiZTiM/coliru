int main()
{
    struct example
    {
        int non_const_member_object = 0 ;
        const int const_member_object = 2 ;
        void member_function(int) {}
    };

    using fn_type = void(int) ;
    fn_type example::*pmfn = &example::member_function ;
    
    void  (example::*pmfn2)(int) = &example::member_function ;
    
    return pmfn == pmfn2 ? 0 : 1 ;
}

    