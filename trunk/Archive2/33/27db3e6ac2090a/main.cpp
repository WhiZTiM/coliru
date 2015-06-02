#include <iostream>
#include <cmath>
#include <algorithm>
#include <string>
#include <deque>
#include <cstring>
#include <cstdio>
#include <vector>
#include <set>
#include <map>
#include <queue>
#include <cstdlib>
#include <iomanip>
#include <stack>
using namespace std;

#define rep(i, a, b) for( i = (a); i <= (b); i++)
#define reps(i, a, b) for( i = (a); i < (b); i++)
#define pb push_back
#define ps push
#define mp make_pair
#define CLR(x,t) memset(x,t,sizeof x)
#define LEN(X) strlen(X)
#define F first
#define S second
#define Debug(x) cout<<#x<<"="<<x<<endl;


const double euler_r = 0.57721566490153286060651209;
const double pi = 3.141592653589793238462643383279;
const double E = 2.7182818284590452353602874713526;
const int inf=~0U>>1;
const int MOD = int(1e9) + 7;
const double EPS=1e-6;

typedef long long LL;

const int M = 34430;
int ok[M + 10], p[M + 10];

void init()
{
    int k = 0;
    for(int i = 2; i < M; i++)
    {
        if(!ok[i]) p[k++] = i;
        for(int j = 0; j < k && i * p[j] < M; j++)
        {
            ok[i * p[j]] = 1;
            if(i % p[j] == 0) break;
        }
    }
    cout << "k = " << k << endl;

}

bool is_prime(LL x)
{
    for(LL i = 2; i * i <= x; i++)
    {
        if(x % i == 0) return false;
    }
    return true;
}

bool judge(int x, int y)
{
    int f[10] = {1, 10, 100, 1000, 10000, 100000, 1000000};
    int weishu1 = log10(x) + 1;
    LL a = 1LL * y * f[weishu1] + x;
    int weishu2 = log10(y) + 1;
    LL b = 1LL * x * f[weishu2] + y;
    if(is_prime(a) && is_prime(b)) return true;
    return false;
}

int main()
{


    init();
    //M = 1000, k = 168;
    //M = 10000, k = 1229;
    //M = 100000, k = 9592;
    int k = 3678, a[10], x, y, z, w, u, sum = inf;

    cout << "************" << endl;



    for(a[1] = 0; a[1] < k; a[1]++) for(a[2] = a[1] + 1; a[2] < k; a[2]++)
    {
        x = p[a[1]]; y = p[a[2]];
        if(judge(x, y) == false) continue;
        for(a[3] = a[2] + 1; a[3] < k; a[3]++)
        {
            z = p[a[3]];
            if(judge(x, z) == false || judge(y, z) == false) continue;
            for(a[4] = a[3] + 1; a[4] < k; a[4]++)
            {
                w = p[a[4]];
                if(judge(x, w) == false || judge(y, w) == false || judge(z, w) == false) continue;
                for(a[5] = a[4] + 1; a[5] < k; a[5]++)
                {
                    u = p[a[5]];
                    if(judge(x, u) == false || judge(y, u) == false || judge(z, u) == false || judge(w, u) == false) continue;
                    else
                    {
                        //cout << x << " " << y << " " << z << " " << w  << " " << u << endl;
                        //cout << "sum  = " << x + y + z + w + u << endl;
                        //goto Z;
                        int uu = x + y + z + w + u;
                        if(sum > uu)
                        {
                            sum = uu;
                            cout << uu << endl;
                        }
                        //sum = sum <  ? sum : x + y + z + w + u;
                    }
                }
            }
        }
    }

    Z:{}
   // cout << sum << endl;
    cout << "************" << endl;
    return 0;
}
