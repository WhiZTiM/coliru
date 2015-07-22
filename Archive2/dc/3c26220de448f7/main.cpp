#include <iostream>
using namespace std;

char checkUeCategory0_v2(int crnti, int xsfn)
{   
    char ret='G';
    
    //UL
    int iPatternIndex =  (xsfn + 12 - (crnti % 8))  % 8 ;   
    int aaa = (iPatternIndex < 3) ? 1 : 0 ;
    //cout << "#shift: " << crnti % 8 <<", tti: "<< xsfn << " isUL: " << aaa << endl;
    if (aaa)
        return 'U';
    
    //DL
    iPatternIndex =  (xsfn + 8 - (crnti % 8))  % 8 ;  
    aaa = (iPatternIndex < 3) ? 1 : 0 ;
    //cout << "#shift: " << crnti % 8 <<", tti: "<< xsfn << " isDL: " << aaa << endl;
    if (aaa)
        return 'D';
    
    return ret;
}

int main()
{
    char tab[40]={};
    int ii[8] = {0,4,1,5,2,6,3,7};
    
    for (int i=0; i < 8; ++i)
    {
        for (int j=0; j<40; ++j)
        {
            cout<<" "<<checkUeCategory0_v2(ii[i],j);
            if (j%10 ==9) 
                cout<<"|";
        }
        
        cout<<" #shift "<<ii[i]<<endl;
    }
}
