#include<bits/stdc++.h>
using namespace std;
using ll=long long;
using ull=unsigned long long;
using i128=__int128_t;
using pis=pair<ll,ll>;

const int N=2e5+100;
const int mod=998244353;

vector<vector<int>> e,col2v,ve;
int n,dfn[N],fa[N][21],col[N],h[N],tim,stk[N<<2],top;
ll ans;

void dfs(int now,int pre){
    dfn[now]=++tim;
    fa[now][0]=pre;
    for(int i=1;i<=20&&(1<<i)<=h[now];i++){
        fa[now][i]=fa[fa[now][i-1]][i-1];
    }
    for(auto to:e[now]){
        if(to==pre)continue;
        h[to]=h[now]+1;
        dfs(to,now);
    }
}

int lca(int a,int b){
    if(h[a]<h[b])swap(a,b);
    int d=h[a]-h[b];
    for(int i=0;i<=20;i++){
        if(d&(1<<i)){
            a=fa[a][i];
        }
    }
    if(a==b)return a;
    for(int i=20;i>=0;i--){
        if(h[a]<(1<<i))continue;
        if(fa[a][i]!=fa[b][i]){
            a=fa[a][i];
            b=fa[b][i];
        }
    }
    return fa[a][0];
}

void vadd(int a,int b){
    ve[a].push_back(b);
    ve[b].push_back(a);
}

ll dp(int now,int pre,int k){
    ll ret=1,cnt=0,sum=0;
    for(auto to:ve[now]){
        if(to==pre)continue;
        ll tmp=dp(to,now,k);
        ret=ret*(tmp+1)%mod;
        sum=(sum+tmp)%mod;
        cnt++;
    }
    if(col[now]!=k)ret=(ret-1+mod)%mod;
    ve[now].clear();
    if(col[now]==k)ans=(ans+ret)%mod;
    else ans=(ans+ret-sum+mod)%mod;
    return ret;
}

void solve(){
    cin>>n;
    e.resize(n+1);ve.resize(n+1);//虚树
    col2v.resize(n+1);
    for(int i=1;i<=n;i++){
        cin>>col[i];
        col2v[col[i]].push_back(i);
    }
    for(int i=1;i<=n-1;i++){
        int u,v;
        cin>>u>>v;
        e[u].push_back(v);
        e[v].push_back(u);
    }
    dfs(1,0);
    for(int i=1;i<=n;i++){
        if(col2v[i].empty())continue;
        sort(col2v[i].begin(),col2v[i].end(),[&](int a,int b){
            return dfn[a]<dfn[b];
        });
        if(col2v[i].front()!=1)stk[++top]=1;
        for(auto p:col2v[i]){
            if(!top){
                stk[++top]=p;
                continue;
            }
            int lc=lca(p,stk[top]);
            if(lc!=stk[top]){
                while(top>1&&dfn[stk[top-1]]>dfn[lc]){
                    vadd(stk[top],stk[top-1]);
                    top--;
                }
                vadd(lc,stk[top--]);
                if(!top||dfn[stk[top]]!=dfn[lc])stk[++top]=lc;
            }
            stk[++top]=p;
        }
        while(top>1)vadd(stk[top],stk[top-1]),top--;
        top=0;
        dp(1,0,i);
    }
    cout<<ans<<'\n';
    // int x,y;
    // while(cin>>x>>y)cout<<lca(x,y)<<'\n';
}

signed main(){
  freopen("aa.in", "r", stdin);
  freopen("aa.out", "w", stdout);
  std::ios::sync_with_stdio(0);
  std::cin.tie(0);
  std::cout.tie(0);
  int t = 1;
//   std::cin>>t;  
  while (t--)
    solve();
}