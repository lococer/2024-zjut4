#include <bits/stdc++.h>

using namespace std;
using ll=long long;
using pis=pair<ll,ll>;

const int N=1e6+1000;
const int maxn=1e6+100;

const ll mod=998244353;
const ll inv2=499122177;


void fmt_or(ll *f,int n,bool inv=false){
    ll k=inv?(mod-1):1;
    for(int i=0;i<n;i++){
        for(int j=0;j<(1<<n);j++){
            if(j&(1<<i))f[j]=(f[j]+k*f[j^(1<<i)]%mod)%mod;
        }
    }
}

void fmt_and(ll *f,int n,bool inv=false){
    ll k=inv?(mod-1):1;
    for(int i=0;i<n;i++){
        for(int j=0;j<(1<<n);j++){
            if(j&(1<<i))f[j^(1<<i)]=(f[j^(1<<i)]+k*f[j]%mod)%mod;
        }
    }
}

void fwt_xor(ll *f, int n,bool inv=false) {
    ll x=inv?inv2:1;
    n=1<<n;
	for (int o = 2, k = 1; o <= n; o <<= 1, k <<= 1){
		for (int i = 0; i < n; i += o){
			for (int j = 0; j < k; j++){
				f[i+j]=(f[i+j]+f[i+j+k])%mod;
				f[i+j+k]=((f[i+j]-f[i+j+k]-f[i+j+k])%mod+mod)%mod;
				f[i+j]=f[i+j]*x%mod, f[i+j+k]=f[i+j+k]*x%mod;
            }
        }
    }
}

ll n,A[N],B[N],a[N],b[N];

void solve(){
    cin>>n;
    for(int i=0;i<(1<<n);i++)cin>>A[i];
    for(int i=0;i<(1<<n);i++)cin>>B[i];
    for(int i=0;i<(1<<n);i++)a[i]=A[i],b[i]=B[i];
    fmt_or(a,n);fmt_or(b,n);
    for(int i=0;i<(1<<n);i++)a[i]=a[i]*b[i]%mod;
    fmt_or(a,n,1);
    for(int i=0;i<(1<<n);i++)cout<<a[i]<<" ";;
    cout<<'\n';

    for(int i=0;i<(1<<n);i++)a[i]=A[i],b[i]=B[i];
    fmt_and(a,n);fmt_and(b,n);
    for(int i=0;i<(1<<n);i++)a[i]=a[i]*b[i]%mod;
    fmt_and(a,n,1);
    for(int i=0;i<(1<<n);i++)cout<<a[i]<<" ";;
    cout<<'\n';

    for(int i=0;i<(1<<n);i++)a[i]=A[i],b[i]=B[i];
    fwt_xor(a,n);fwt_xor(b,n);
    for(int i=0;i<(1<<n);i++)a[i]=a[i]*b[i]%mod;
    fwt_xor(a,n,1);
    for(int i=0;i<(1<<n);i++)cout<<a[i]<<" ";;
    cout<<'\n';
}

signed main(){
    ios::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);
    int t=1;
    // cin>>t;
    while(t--)solve();
}
/*

*/