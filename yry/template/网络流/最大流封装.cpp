#include<bits/stdc++.h>
using namespace std;
using ll=long long;
#define int ll
const int inff=2e17;
struct MaxFlow{
    int n,m,S,T,tot=1;vector<int>to,flow,cur,d;vector<vector<int>>es;
    MaxFlow(int n,int m):n(n),m(m),to(m),flow(m),cur(n),d(n),es(n){}
    void Add(int u,int v,int w){to[++tot]=v;flow[tot]=w;es[u].push_back(tot); }
    void Addedge(int u,int v,int w){Add(u,v,w);Add(v,u,0);}
    bool BFS(){d.clear();d.resize(n);d[S]=1;queue<int>q;q.push(S);while(!q.empty())
        {int x=q.front();q.pop();cur[x]=0;for(auto k:es[x]){int u=to[k];
             if(flow[k]&&!d[u])d[u]=d[x]+1,q.push(u);}}return d[T];}
    int DFS(int x,int now){if(x==T||!now)return now;int res=now;
        for(int i=cur[x];i<(int(es[x].size()))&&res>0;i++)
            {cur[x]=i;int k=es[x][i],u=to[k],w=flow[k];if(!w||d[u]!=d[x]+1)continue;
                int opt=DFS(u,min(res,w));res-=opt,flow[k]-=opt,flow[k^1]+=opt;}return now-res;}
    ll Solve(int _s,int _t){ll ans=0;S=_s;T=_t;while(BFS())ans+=DFS(S,inff);return ans;}};
void Solve()
{
    int n,m,s,t;cin>>n>>m>>s>>t;MaxFlow A(n+5,2*m+5);
    for(int i=1,u,v,w;i<=m;i++)cin>>u>>v>>w,A.Addedge(u,v,w);cout<<A.Solve(s,t)<<'\n';
}