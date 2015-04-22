#include<stdio.h>
char c[102][102];
struct node{
    int x,y;
}a[1000001];
int b[102][102];
int main(){
    int n,m;
    scanf("%d%d",&n,&m);
    for(int i=1;i<=n;i++){
        for(int j=1;j<=m;j++){
            scanf(" %c",&c[i][j]);
        }
    }
    int p=0,q=1;
    a[p].x=1,a[p].y=1;
    b[a[p].x][a[p].y]=1;
    
    
    while(p<=q){
        
        if((c[a[p].x][a[p].y]=='D'||c[a[p].x][a[p].y]=='B')&&(b[a[p].x+1][a[p].y]!=b[a[p].x][a[p].y]-1||b[a[p].x+1][a[p].y]==0)){
            
            if(b[a[p].x+1][a[p].y]==b[a[p].x][a[p].y]+1){
                printf("%d\n%d %d",b[a[p].x][a[p].y]+1,a[p].x+1,a[p].y);
                break;
            }else {
                b[a[p].x+1][a[p].y]=b[a[p].x][a[p].y]+1;
                a[q].x=a[p].x+1;
                a[q].y=a[p].y;
                q++;
            }
        }
        
        if((c[a[p].x][a[p].y]=='R'||c[a[p].x][a[p].y]=='B')&&(b[a[p].x+1][a[p].y]!=b[a[p].x][a[p].y]-1||b[a[p].x][a[p].y+1]==0)){
            
            if(b[a[p].x][a[p].y+1]==b[a[p].x][a[p].y]+1){
                printf("%d\n%d %d",b[a[p].x][a[p].y]+1,a[p].x,a[p].y+1);
                break;
            }else {
                b[a[p].x][a[p].y+1]=b[a[p].x][a[p].y]+1;
                a[q].x=a[p].x;
                a[q].y=a[p].y+1;
                q++;
            }
        }
        
        if((c[a[p].x-1][a[p].y]=='D'||c[a[p].x-1][a[p].y]=='B')&&(b[a[p].x-1][a[p].y]!=b[a[p].x][a[p].y]-1||b[a[p].x-1][a[p].y]==0)){
            
            if(b[a[p].x-1][a[p].y]==b[a[p].x][a[p].y]+1){
                printf("%d\n%d %d",b[a[p].x][a[p].y]+1,a[p].x-1,a[p].y);
                break;
            }else {
                b[a[p].x-1][a[p].y]=b[a[p].x][a[p].y]+1;
                a[q].x=a[p].x-1;
                a[q].y=a[p].y;
                q++;
            }
        }
        
        if((c[a[p].x][a[p].y-1]=='R'||c[a[p].x][a[p].y-1]=='B')&&(b[a[p].x][a[p].y-1]!=b[a[p].x][a[p].y]-1||b[a[p].x][a[p].y-1]==0)){
            
            if(b[a[p].x][a[p].y-1]==b[a[p].x][a[p].y]+1){
                printf("%d\n%d %d",b[a[p].x][a[p].y]+1,a[p].x,a[p].y-1);
                break;
            }else {
                b[a[p].x][a[p].y-1]=b[a[p].x][a[p].y]+1;
                a[q].x=a[p].x;
                a[q].y=a[p].y-1;
                q++;
            }
        }

        p++;
    }
    
}
    
