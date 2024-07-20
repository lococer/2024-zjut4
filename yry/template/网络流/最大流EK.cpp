#include<bits/stdc++.h>
using namespace std;
using ll=long long;
using pis=pair<int,int>;
const int N=1e6+5;


/*


会爆int



*/




int edge[N],head[N],w[N],next[N],id=0,lim[N];//限流
int pre[N];
int n,m,s,t;
bool vis[N];
ll ans=0;

void add_e(int u,int v,int w_){
    edge[id]=v;
    w[id]=w_;
    ::next[id]=head[u];
    head[u]=id++;
    

}


bool bfs(){
    memset(vis,false,n*sizeof(bool));
    queue<int> dl;
    dl.push(s);
    while(!dl.empty()){
        int now=dl.front();
        dl.pop();
        if(vis[now])continue;
        vis[now]=true;
        for(int i=head[now];i!=-1;i=::next[i]){
            int to=edge[i];
            if(!vis[to]&&w[i]>0){
                lim[to]=min(lim[now],w[i]);
                pre[to]=i;
                dl.push(to);
                if(to==t)return true;
            }
        }
    }
    return false;
}

void ek(){
    ans=0;
    while(bfs()){
        ans+=lim[t];
        int now=t;
        while(now!=s){
            int id=pre[now];
            w[id]-=lim[t];
            w[id^1]+=lim[t];
            now=edge[id^1];
        }
    }
}

void solve(){
    cin>>n>>m>>s>>t;
    s--;t--;
    lim[s]=0x3f3f3f3f;
    for(int i=0;i<=n;i++)head[i]=-1;
    int p[n][n];
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
    ek();
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