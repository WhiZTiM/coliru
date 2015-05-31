#include <iostream>
#include <string>
#include <unordered_map>

using namespace std;

int main (void)
{
    unordered_map<string,string> myhash;
    int i,n,m,len1,len2;
    cin>>n>>m;
    string arr2[3010];
    string s1,s2;
    for ( i = 0; i < m; i++ )
    {
        cin>>s1>>s2;
        myhash.emplace(s1,s2);
    }
    for ( i = 0; i < n; i++ )
    {
        cin>>arr2[i];
    }
    for ( i = 0; i < n; i++ )
    {
        len1 = arr2[i].length();
        len2 = myhash[arr2[i]].length();
        if ( len1 > len2 )
            cout<<myhash[arr2[i]]<<"\t";
        else
            cout<<arr2[i]<<"\t";
    }
    cout<<"\n";
    return 0;
}