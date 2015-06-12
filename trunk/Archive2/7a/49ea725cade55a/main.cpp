
#define rss_str "Rss"
#define shared_str "Shared"
#define private_str "Private"
#define swap_str "Swap"
#define pss_str "Pss"
#define referenced_str "Referenced"
#define sep ':'
#define readopenfile "r"
#define i int
#define s std::string
#define l(A) (new s(A))->length()
#define conc(...) str(__VA_ARGS__).c_str()
#define eq(A,B) strncmp(A,B,l(A))==0
#define fun(B) strchr(B,sep)+1
#define smap std::map<s,i>
#define foreach(m) for(auto it : m) { auto a = it.first; auto b = it.second;
#define foreachend }
#define strs std::stringstream
#define beginfile(F) FILE *fp = fopen(F(), readopenfile);
#define endfile fclose(fp);

template<class A> s str(A a)                        { strs ss; ss<<a; return ss.str(); }
template<class A, class ... B> s str(A a, B...b)    { strs ss; ss<<a<<str(b...); return ss.str(); }
template<class A, class X>
void add(smap &m, X x, A a) { if(eq(a,x))m[a] += atoi(fun(x));}
template<class A, class X, class ... B>
void add(smap &m, X x, A a, B...b) { if(eq(a,x))m[a] += atoi(fun(x)); add(m, x, b...); }

const char* name() { return conc("/proc/",getpid(),"/smaps"); }

i main(i __attribute__((unused)) argc, char __attribute__((unused)) *args[])
{
    char b[256];
    smap m;

    beginfile(name)
        while(fgets(b, 256, fp))
            add(m,b,rss_str,shared_str,private_str,swap_str,pss_str,referenced_str);

        foreach(m)
            i value = b;
            fprintf(stderr, "%s: %d\n", a.c_str(), b);
        foreachend
    endfile

    return 1;
}