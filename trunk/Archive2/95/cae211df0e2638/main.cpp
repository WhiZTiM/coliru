    struct A
    {
        int *p;
    };
    
    int main()
    {
		{
			A *a = new A();
			a->p = new int(0);
			a->*p = 5;
		}
		
		{
			A a;
			a.p = new int(0);
			a.*p = 5;
		}
    	
    	return 0;
    }