#include <cstdio>
#include <queue>
#include <vector>
#include <algorithm>
#define LARGE 1000000000
using std::vector;
using std::priority_queue;
using std::max;
struct State{
    int node,weight;
    State(int n,int w){
        node=n;
        weight=w;
    }
};
typedef bool(*compare_t)(const State&,const State&);
bool compare_func(const State &a,const State &b){
    return a.weight>b.weight; //this causes the priority_queue to return nodes with lower weights when queue.top() is called
}
int main(){
    int T; //test cases
    scanf("%d",&T);
    for(int i=1;i<=T;++i){
        int n,m;
        scanf("%d %d",&n,&m);
        int adj_mat[n][n],cost[n];
        for(int i=0;i<n;++i){
            for(int j=0;j<n;++j){
                adj_mat[i][j]=LARGE;
            }
            cost[i]=LARGE;
        }
        for(int i=0;i<m;++i){
            int u,v,w;
            scanf("%d %d %d",&u,&v,&w);
            adj_mat[u][v]=w;
            adj_mat[v][u]=w;
        }
        int source;
        scanf("%d",&source);
        
        priority_queue<State,vector<State>,compare_t> node_queue(compare_func);
        node_queue.push(State(source,0));
        while(!node_queue.empty()){
            State top=node_queue.top();
            node_queue.pop();
            if(cost[top.node]==LARGE){
                cost[top.node]=top.weight;
                for(int i=0;i<n;++i){
                    if(adj_mat[top.node][i]!=LARGE){
                        node_queue.push(State(i,max(top.weight,adj_mat[top.node][i])));
                    }
                }
            }
        }
        printf("Case %d:\n",T);
        for(int i=0;i<n;++i){
            if(cost[i]==LARGE)printf("Impossible\n");
            else printf("%d\n",cost[i]);
        }
    }
    return 0;
}