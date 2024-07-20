#include<bits/stdc++.h>
using namespace std;
using ll=long long;
using pis=pair<int,int>;
const int N=1e6+5;
ll p[N],w[N];

int find(int a){
    if(p[a]!=a){
        int t=p[a];
        p[a]=find(p[a]);
        w[a]+=w[t];
    }
    return p[a];
}

void un(int a,int b,int c){
    int pa=find(a),pb=find(b);
    if(pa!=pb){
        p[pa]=pb;
        w[pa]=c+w[b]-w[a];
    }
}




void solve(){
    int n,m;
    cin>>n>>m;
    for(int i=0;i<n;i++)p[i]=i,w[i]=0;
    bool ok=true;
    for(int i=0;i<m;i++){
        ll a,b,c;
        cin>>a>>b>>c;
        a--;b--;
        if(find(a)==find(b)){
            ok&=(c==w[a]-w[b]);
        }else{
            un(a,b,c);
        }
    }
    cout<<(ok?"Yes\n":"No\n");
}


int main(){
    #ifndef ONLINE_JUDGE
    freopen("../temp/aa.in", "r", stdin);
    freopen("../temp/aa.out", "w", stdout);
    #endif 
    std::ios::sync_with_stdio(0);std::cin.tie(0);std::cout.tie(0);
    int t=1;std::cin>>t;
    while(t--)
        solve();
}