#include <bits/stdc++.h>
// #include<algorithm>

using namespace std;
using ll = long long;
using pis = pair<int, int>;

const int N=1e5+100;
ll sum1[N],sum2[N];

inline ll lowbit(ll x){return x&(-x);}

void update1(ll p,ll k){
    for(ll i=p;i<=N;i+=lowbit(i)){
        sum1[i]+=k;
        sum2[i]+=p*k;
    }
}

void update(ll l,ll r,ll k){
    update1(l,k);update1(r+1,-k);
}

ll query1(ll p){
    ll ans=0;
    for(ll i=p;i;i-=lowbit(i)) ans+=(p+1)*sum1[i]-sum2[i];
    return ans;
}

ll query(ll l,ll r){
    return query1(r)-query1(l-1);
}


void solve()
{
    int n,m;
    cin>>n>>m;
    for(int i=0;i<n;i++){
        ll tmp;
        cin>>tmp;
        update(i+1,i+1,tmp);
    }
    for(int i=0;i<m;i++){
        int op,x,y,k;
        cin>>op;
        if(op==1){
            cin>>x>>y>>k;
            update(x,y,k);
        }else{
            cin>>x>>y;
            cout<<query(x,y)<<'\n';
        }
    }

}

signed main()
{

    std::ios::sync_with_stdio(0);
    std::cin.tie(0);
    std::cout.tie(0);
    int t = 1;  //cin>>t;
    while (t--)
        solve();
}