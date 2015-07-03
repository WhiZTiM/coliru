#include <iostream>
#include <cstring>

        constexpr bool is_path_sep(char c) {
            return c == '/' || c == '\\';
        }
        
        constexpr const char* strip_path(const char* path)
        {
            auto lastname = path;
            for (auto p = path ; *p ; ++p) {
                if (is_path_sep(*p) && *(p+1)) lastname = p+1;
            }
            return lastname;
        }
        
        void test(char const* path, char const* exp) {
            char const* act = strip_path(path);
            if(0 != std::strcmp(act, exp)) {
                std::cout << "test failed! expected: \""<<exp<<"\" but got: \""<< act<<"\"\n";
            }
        }
        
        int main()
        {
            test("", "");
            test("foo.h", "foo.h");
            test("foo/h", "h");
            test("/foo", "foo");
            test("foo/", "foo/");
            test("foo/bar", "bar");
            test("/foo/bar", "bar");
            test("/foo/bar/", "bar/");
            test("/foo/bar/x.y", "x.y");
        }