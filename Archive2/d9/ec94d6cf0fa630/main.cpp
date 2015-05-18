#include<fstream>
#include<vector>
#include<set>
#include<iomanip>


using namespace std;

int i,j;
set<int> used_pix;

int G[30][30];

void push_triangle_1(int a){
    if(a-5>=1&& a%5!=0){

    G[a][a-5]=1;
    G[a-5][a]=1;

    G[a][a+1]=1;
    G[a+1][a]=1;

    G[a-5][a+1]=1;
    G[a+1][a-5]=1;

    used_pix.insert(a);
    used_pix.insert(a-5);
    used_pix.insert(a+1);
    }
    }
void push_triangle_2(int a){
    if(a-5>=1&& a%5!=1){

    G[a][a-5]=1;
    G[a-5][a]=1;

    G[a][a-1]=1;
    G[a-1][a]=1;

    G[a-5][a-1]=1;
    G[a-1][a-5]=1;

    used_pix.insert(a);
    used_pix.insert(a-5);
    used_pix.insert(a-1);
    }
    }

void push_triangle_3(int a){
    if(a+5>=1&& a%5!=0){

    G[a][a+5]=1;
    G[a+5][a]=1;

    G[a][a+1]=1;
    G[a+1][a]=1;

    G[a+5][a+1]=1;
    G[a+1][a+5]=1;

    used_pix.insert(a);
    used_pix.insert(a+5);
    used_pix.insert(a+1);
    }
    }
void push_triangle_4(int a){
    if(a+5>=1&& a%5!=1){

    G[a][a+5]=1;
    G[a+5][a]=1;

    G[a][a-1]=1;
    G[a-1][a]=1;

    G[a+5][a-1]=1;
    G[a-1][a+5]=1;

    used_pix.insert(a);
    used_pix.insert(a+5);
    used_pix.insert(a-1);
    }
    }


int main(){
    ofstream cout("output.txt");

 //   for(i=1;i<=25;i++) T.push_back(i);
  //    random_shuffle(T.begin(),T.end());


   push_triangle_1(18);
   push_triangle_3(23);


cout<<"    ";
for(i=1;i<=25;i++) cout<<setw(3)<<i;
cout<<endl;
for(i=1;i<=25;i++) {
    cout<<setw(2)<<i<<": ";
    for(j=1; j<=25;j++) cout<<setw(3)<<G[i][j];
    cout<<endl;
    }


for(set<int>::iterator t=used_pix.begin(); t!=used_pix.end();t++) cout<<*t<<' ';


    }
