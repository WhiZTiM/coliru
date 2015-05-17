#include <algorithm>
#include <vector>
#include <map>
#include <iostream>


std::map <int, std::map <int, int> > M;
std::map <int, std::map <int, int> > M1;

int StoI(std::string s){
   if (s=="odd") return -1;
   return 1;
}
int sum(int a, int b){
   if (a==b) return 1;
   return -1;
}


main() {
#ifndef ONLINE_JUDGE
   freopen("input1.txt", "rt", stdin);
   freopen("output.txt", "wt", stdout);
#endif
    long int N; bool f=false;//length
    int A, x, y, cur, res; //unswers
    std::string S; 
    
    while (true){
    	std::cin >> N; if (N==-1) return 0;
	   	
		std::cin >> A;
		
		M.clear(); M1.clear(); f=false;
		
		for (int i=0; i<A; i++){
			std::cin >> x >> y >> S;
		
			if (f) continue;
				
			if (y > N || x > y || (x==y && S=="even")){
				std::cout << i << std::endl, f=true; 
				continue;
			}
				
			cur = StoI(S);
			if (!f && M[x][y]!=0 && M[x][y]!=cur) {std::cout << i << std::endl, f = true;  continue;}		
			M[x][y]=M1[y][x]=cur;
			if (M.find(y+1)!=M.end()){
				for (std::map<int, int>::iterator it = M[y+1].begin(); it!=M[y+1].end() && !f;it++){
					res = sum(M[y+1][(*it).first], cur);
					if (M[x][(*it).first]!=0 && M[x][(*it).first]!=res){std::cout << i << std::endl, f = true;  continue;}	
					M[x][(*it).first] = M1[(*it).first][x] =res;
					
				}
			}
			
		
			if (M1.find(x-1)!=M1.end()){
				std::map<int, int>::iterator it = M1[x-1].end();
				it--;
				while(!f){
					res = sum(M1[x-1][(*it).first], cur);
					if (M1[y][(*it).first]!=0 && M1[y][(*it).first]!=res){std::cout << i << std::endl, f = true;  continue;}	
					M1[y][(*it).first] = M[(*it).first][y] =res;
					if (it==M1[x-1].begin()) break;
					it--;
				}

			}
			
			

			
		}
		if (!f) std::cout << A << std::endl;
   }	   
}   
	
    