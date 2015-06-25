void non_member_function(int) {}

int main()
{
    struct example
    {
        void unqualified_member_function(int) {}
        static void static_member_function(int) {}

        void const_qualified_member_function(int) const {}
        void ref_qualified_member_function(int) & {}
    };

    using member_or_non_member_fn_type = void(int) ;
    member_or_non_member_fn_type example::*pmfn = &example::unqualified_member_function ;
    member_or_non_member_fn_type* pfn = non_member_function ;
    pfn = &example::static_member_function ;

    using const_qualified_member_fn_type = void(int) const ;
    const_qualified_member_fn_type example::*pmfnc = &example::const_qualified_member_function ;

    using ref_qualified_member_fn_type = void(int) & ;
    ref_qualified_member_fn_type example::*pmfnr = &example::ref_qualified_member_function ;
}
