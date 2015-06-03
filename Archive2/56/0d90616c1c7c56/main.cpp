#include <iostream>
#include <cstdio>
#include <cmath>
#include <algorithm>
#include <string>

using namespace std;

int main() {
    // your code goes here
	int t,kommt[1000],geht[1000],da[1000],n;
	cin >> t;
	while(t--)
	{
	scanf("%i",&n);
	for(int i=0;i<1000;i++)
	    da[i]=0;
	for(int i=0;i<n;i++)
	    scanf("%i",&kommt[i]);
	for(int i=0;i<n;i++)
	    scanf("%i",&geht[i]);
	for(int i=kommt[i];i<geht[i]-1;i++)
	    da[i]++;
	
	int m=-1;
	for(int i=0;i<1000;i++)
	    m=(da[i]>m) ? da[i] : m;
	cout << m << endl;
	
	}
	return 0;
}
