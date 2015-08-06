int n;
typedef struct vars{int c[n];} vars_t;
vars_t v;

f(){n=2;}
g(){int b[n];}

main(){
        int a[n];
        f();
        g();
}