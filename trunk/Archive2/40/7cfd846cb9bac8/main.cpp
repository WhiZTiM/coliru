extern char* strchr(char* haystack, char needle) {
    for(; *haystack != '\0'; ++haystack) {
        if(*haystack == needle) return haystack;
    }
    return nullptr;
}

inline char const* strchr(char const* haystack, char needle) {
    return strchr(const_cast<char*>(haystack), needle);
}

int main()
{
    char const* p = "hello world";
    strchr(p, 'w');
}