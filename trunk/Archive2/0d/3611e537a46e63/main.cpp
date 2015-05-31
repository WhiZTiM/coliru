#include<bits/stdc++.h>
using namespace std;
int x[10]={0,2,2,-2,-2,1,1,-1,-1};
int y[10]={0,1,-1,1,-1,2,-2,2,-2};
int bfs(int a1,int b1,int a2,int b2)
{
    pair<int,int> p;
    int i;
    queue<pair<int,int> >q;
    int moves[9][9],visit[9][9],m,n;
    memset(moves,0,sizeof(moves));
    memset(visit,0,sizeof(visit));
    p.first=a1;
    p.second=b1;
    q.push(p);
    moves[a1][b1]=0;
    while(!q.empty())
    {
        p=q.front();
        q.pop();
        if(p.first==a2&&p.second==b2)
            return moves[a2][b2];
        for(i=1;i<=8;i++)
        {
            m=p.first+x[i];
            n=p.second+y[i];
            if(m>8||m<1||n>8||n<1)
                continue;
            else
            {
                visit[m][n]=1;
                moves[m][n]=moves[p.first][p.second]+1;
                q.push(make_pair(m,n));
            }
        }
    }
}


int main()
{
    string d1 = "a1", f1 = "h8", d2 = "a1", f2 = "c2", d3 = "h8", f3 = "c3";
    cout << bfs((int)(d1[0]-'a')+1,(int)(d1[1] - '0'),(int)(f1[0]-'a')+1,(int)(f1[1] - '0')); cout << endl ;
    cout << bfs((int)(d2[0]-'a')+1,(int)(d2[1] - '0'),(int)(f2[0]-'a')+1,(int)(f2[1] - '0')); cout << endl ;
    cout << bfs((int)(d3[0]-'a')+1,(int)(d3[1] - '0'),(int)(f3[0]-'a')+1,(int)(f3[1] - '0')); cout << endl ;
    return 0;
}