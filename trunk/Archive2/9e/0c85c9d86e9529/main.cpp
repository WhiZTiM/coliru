// trimble.cpp : for Job interview 10 Aug 2015 by Jabez Lim(jabezlim@naver.com)
//
 
#include <iostream>
#include <limits>
#include <cstdlib>
#include <cstring>
#include <cstdio>
 
using namespace std;
#define MAXLEN    	500000
#define MAX(a,b)	(a>b)?a:b
 
class LongNumber {
private:
	char num[8];
	char tmp[MAXLEN];
	char strnum[MAXLEN];
	int  idx, idx1;
 
protected:
	friend ostream& operator<<(ostream& os, LongNumber& longnum) {
		int rit;
		if (longnum.idx==0) os << "0";
		else {
			for (rit = longnum.idx - 1; rit >= 0; --rit)
				os << (char)(longnum.strnum[rit] + '0');
		}
		return os;
	}
 
public:
	LongNumber() { idx = idx1 = 0; }
	LongNumber(int n) { set(n); }
	void	empty() { idx = 0; }
	void	set(int n);
	int		getReverse() { 
		char buf[8];
		int i;
		for (i = 0; i < idx1; i++) buf[i] = num[i] + '0';
		buf[i] = 0;
		return atoi(buf); 
	}
	int		multiply();
	void	power(int m);
};
 
void LongNumber::set(int n) {
	idx = idx1 = 0;
	while (n) {
		num[idx1++] = (n % 10);
		strnum[idx++] = (n % 10);
		n = n / 10;
	}
}
 
int  LongNumber::multiply() {
	int maxlen = idx+idx1;	
	int i, n = 0, ov, m, len1 = 0, len = idx1;
	for (i = 0; i < maxlen; i++) tmp[i] = 0;	
	int it1, it2;
	for (it1 = 0; it1 < idx1; it1++)
	{
		m = n;
		for (it2 = 0; it2 < idx; it2++)
		{
			ov = num[it1]*strnum[it2] + tmp[m];
			tmp[m] = ov % 10;
			ov = ov / 10;
			if (ov) {
				tmp[m + 1] += ov;
				len1 = MAX(len1, m+2);
			}			
			m++;
		}
		n++;
	}
	len1 = MAX(len1, m);
	empty();
	memcpy(strnum, tmp, len1);
	idx = len1;
	return idx;
}
 
void LongNumber::power(int m)
{
	if (m == 0) set(1);
	else {
		for (int i = 1; i < m; i++) {
			multiply(); printf("[%d:%d]\n", i, idx);
		}
	}
}
 
int main(int argc, char* argv[])
{
	int n = -1, m;
	LongNumber	number;		
	while (n < 0 || n>99999) {		
		cout << "Enter a number (0-99999): ";
		cin.clear();
		cin >> n;
		if (!cin) {
			cin.clear();
			cin.ignore(numeric_limits<streamsize>::max(), '\n');
		}
	}
 
	number.set(n);	
	m = number.getReverse();
	number.power(m);
 
	cout << "Result: " << n << "^" << m << " is " << number << endl;
	return 0;
}
 