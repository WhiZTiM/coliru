long long expo(int n,int x) {
        long long sum = 1;
        for(int i = n-1; i>0; --i)
                sum = 1 + x * sum / i;
return sum;
}

long long exp(int a,int b) {
        if( b == 0)  return 1;
        if( b % 2 ) return a * exp(a,b-1);
        long long t = exp(a,b/2);
        return t * t;
}
