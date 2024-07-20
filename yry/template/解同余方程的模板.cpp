#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pis = pair<ll, ll>;
using pisi = pair<int, int>;
using tup = tuple<ll, int, int>;
const ll mod=1000000007;
ll ans=0;

inline ll mul(ll a,ll b,ll mod){//O(1)取模快速乘，不会爆long long
	return (a*b-(ll)((long double)a/mod*b)*mod+mod)%mod;
}


ll exgcd(ll a,ll b,ll &x,ll &y){
    if(b==0){
        x=1;y=0;
        return a;
    }
    ll ret=exgcd(b,a%b,x,y);
    ll t1,t2;
    t1=y;t2=x-a/b*y;
    x=t1;y=t2;
    return ret;
}


ll solvemod(const vector<ll> &a,const vector<ll> &m){
    int n=a.size();
    ll a1=a[0],m1=m[0];
    for(int i=1;i<n;i++){
        ll a2=a[i],m2=m[i],k1,k2;
		ll d = exgcd(m1,m2,k1,k2);
		if((a2-a1)%d) return -1;
		else{
			k1 = mul(k1,(a2-a1)/d,m2/d);//这个地方必须要用取模快速乘
			a1 = a1+k1*m1;
			m1 = abs(m1/d*m2);
		}
    }
    return (a1%m1+m1)%m1;
}


int main()
{
    #ifndef ONLINE_JUDGE
    freopen("aa.in", "r", stdin);
    freopen("aa.out", "w", stdout);
    #endif 
    ios::sync_with_stdio(0);
    cin.tie(0);
    
    
    return 0;
}