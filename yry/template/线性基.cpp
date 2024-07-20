#include<bits/stdc++.h>

using namespace std;
using ll=long long;
using tup=tuple<int,int,int>;
using pisd=pair<double,double>;
constexpr int mod=998244353;
constexpr int N=60;//位数
ll p[N+1];//



void ins(ll x){//线性基插入
    for(int i=N;i>=0;i--){
        if(x&(1ll<<i)){
            if(!p[i]){
                p[i]=x;
                return;
            }
            x^=p[i];
        }
    }
}

bool check(ll x){//查询，不插入，成功插入代表不在
    for(int i=N;i>=0;i--){
        if(x&(1ll<<i)){
            if(!p[i])return false;
            x^=p[i];
        }
    }
    return true;
}




void solve(){
    int n;
    cin>>n;
    for(int i=0;i<n;i++){
        ll tmp;
        cin>>tmp;
        ins(tmp);
    }
    ll tmp=0;
    for(int i=N;i>=0;i--){
        if(!p[i])continue;
        if(tmp^p[i]>tmp)tmp^=p[i];
    }
    cout<<tmp;

}

int main(){
    #ifndef ONLINE_JUDGE
    freopen("../temp/aa.in", "r", stdin);
    freopen("../temp/aa.out", "w", stdout);
    #endif 
    std::ios::sync_with_stdio(0);std::cin.tie(0);std::cout.tie(0);
    int t=1;//cin>>t;
    while(t--)
        solve();
}