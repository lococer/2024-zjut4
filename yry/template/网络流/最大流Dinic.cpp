#include<bits/stdc++.h>
using namespace std;
using ll=long long;
using pis=pair<int,int>;
const int N=1e6+5;
/*


会爆int



*/
ll edge[N],head[N],w[N],next[N],id=0;//lim[N];//限流
ll pre[N],level[N];
ll n,m,s,t;
ll ans=0;

void add_e(int u,int v,ll w_){
    edge[id]=v;
    w[id]=w_;
    ::next[id]=head[u];
    head[u]=id++;
}

bool bfs(){//分层
    memset(level,-1,n*sizeof(ll));
    level[s]=0;
    queue<int> dl;
    dl.push(s);
    while(!dl.empty()){
        int now=dl.front();
        dl.pop();
        if(now==t)return true;
        for(int i=head[now];i!=-1;i=::next[i]){
            int to=edge[i];
            if(level[to]==-1&&w[i]){
                level[to]=level[now]+1;
                dl.push(to);
                //if(to==t)return true;
            }
        }
    }
    return level[t]!=-1;
}

ll dfs(int now,ll lim){
    if(now==t)return lim;
    ll tmp=0;
    for(int i=head[now];i!=-1;i=::next[i]){
        int to=edge[i];
        if(w[i]&&level[to]==level[now]+1){//跨层，可改成跨多层
            ll ret=dfs(to,min(lim,w[i]));
            w[i]-=ret;
            w[i^1]+=ret;
            lim-=ret;
            tmp+=ret;
            if(!lim)break;
        }
    }
    if(!tmp)level[now]=-1;//优化,通不过就删点
    return tmp;
}


void dinic(){
    while(bfs()){
        ans+=dfs(s,1000000000000000);
    }
}

void solve(){
    ans=0;
    cin>>n>>m>>s>>t;
    s--;t--;
    //lim[s]=0x3f3f3f3f;
    for(int i=0;i<=n;i++)head[i]=-1;
    ll p[n][n];
    memset(p,0,sizeof(p));
    for(int i=0;i<m;i++){
        int u,v,c;
        cin>>u>>v>>c;
        p[u-1][v-1]+=c;
    }
    for(int i=0;i<n;i++){
        for(int j=0;j<n;j++){
            if(p[i][j]){
                add_e(i,j,p[i][j]);
                add_e(j,i,0);
            }
        }
    }
    dinic();
    cout<<ans<<'\n';
}


int main(){
    #ifndef ONLINE_JUDGE
    freopen("../../temp/aa.in", "r", stdin);
    freopen("../../temp/aa.out", "w", stdout);
    #endif 
    std::ios::sync_with_stdio(0);std::cin.tie(0);std::cout.tie(0);
    int t=1;//std::cin>>t;
    while(t--)
        solve();
}