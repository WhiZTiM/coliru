#include <iostream>
#include <memory>

struct proxy_ostream : public std::ostream
{
    proxy_ostream(std::ostream& source)
		: std::ostream(source.rdbuf())
	{
	}
};

std::unique_ptr<std::ostream> test1(std::ostream& source)
{
    struct local : public std::ostream
    {
	    proxy_ostream dec;
	
	    local(std::ostream& source)
            : std::ostream(dec.rdbuf())
            , dec(source)
        {
        }
    };
    
    return std::make_unique<local>(source);
}

std::unique_ptr<std::ostream> test2(std::ostream& source)
{
	struct local : public std::ostream
	{
		local(std::ostream& source)
			: std::ostream(source.rdbuf())
		{
		}
	};

	return std::make_unique<local>(source);
}

int main()
{

    proxy_ostream dec(std::cout);
    dec << "test1\n";
    
    std::ostream ss(dec.rdbuf());
    ss << "test2\n";
    
    auto p1 = test1(std::cout);
    (*p1) << "test3\n";
    
    auto p2 = test2(std::cout);
    (*p2) << "test4\n";
    return 0;
}
