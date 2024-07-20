#include <bits/stdc++.h>

using namespace std;
using ll = long long;
using pis = pair<ll, ll>;

const int mod = 998244353;
int rev[2100001];
ll F[2100000],G[2100000];
ll qpow(ll a,ll b){
    ll ret=1;
    while(b){
        if(b&1)ret=ret*a%mod;
        b>>=1;
        a=a*a%mod;
    }
    return ret;
}
void NTT(ll *a,int bit,bool inv=false){
    for(int i=0;i<(1<<bit);i++){
        if(i<rev[i])swap(a[i],a[rev[i]]);
    }
    for(int h=1;h<=bit;h++){
        int n=1<<h;
        for(int i=0;i<(1<<bit);i+=(1<<h)){
            ll t=1,w=qpow(3,(mod-1)/n);
            if(inv)w=qpow(332748118,(mod-1)/n);
            for(int j=i;j<i+(n>>1);j++){
                ll tmp=t*a[j+(n>>1)]%mod;
                a[j+(n>>1)]=(a[j]-tmp+mod)%mod;
                a[j]=(a[j]+tmp+mod)%mod;
                t=t*w%mod;
            }
        }
    }
}
int main()
{
    // ios::sync_with_stdio(false);
    // cin.tie(0);
    freopen("aa.in", "r", stdin);
    freopen("aa.out", "w", stdout);

    int n,m,s=0;
    cin>>n>>m;
    n++;m++;
    while((1<<s)<(n+m-1))s++;
    for(int i=0;i<=2100000;i++){
        rev[i]=((rev[i>>1]>>1)|((i&1)<<(s-1)));
    }
    for(int i=0;i<(1<<s);i++)F[i]=G[i]=0;
    for(int i=0;i<n;i++)cin>>F[i];
    for(int i=0;i<m;i++)cin>>G[i];
    NTT(F,s);NTT(G,s);
    for(int i=0;i<(1<<s);i++)F[i]*=G[i];
    NTT(F,s,true);
    ll inv=qpow((1<<s),mod-2);
    for(int i=0;i<m+n-1;i++)(cout<<F[i]*inv%mod)<<" ";
    return 0;
}