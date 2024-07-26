#include <bits/stdc++.h>

using namespace std;
using ll = long long;
// using C=complex<double>;
using i128=__int128;

const int N=1e5+100;
const ll mod=1000000007;
const ll inv2=500000004,inv6=166666668;

ll qpow(ll a,ll b){
    ll ret=1;
    for(;b;b>>=1,a=a*a%mod)if(b&1)ret=ret*a%mod;
    return ret;
}

ll inv(ll x){return qpow(x,mod-2);}

ll dp[35][2],n,k,a[N],num1;

/*
ff在质数处取值与原函数相同,且完全积性
需要ff sumff
*/
struct min_25{
    vector<ll> prim,mark,pref,id1,id2,valm,gx,prex;
    ll MOD,tot,n,qn,cntm;
    min_25()=default;
    // ll(*sumff)(ll);//前缀和,快速求2~n的ff之和
    // ll(*f)(ll,ll);//原函数在p[i]的j次方处的取值
    // ll(*pref)(ll);//原函数在质数处的前缀和
    ll getid(ll m) {
        if(m<=qn) return id1[m];
        else return id2[n/m];
    }
    ll S(ll x,ll y){//ans=f(1)+S(n,0)
        if(prim[y]>=x)return 0;
        ll k=getid(x);
        ll ans=((num1*gx[k]%MOD-pref[y])%MOD+MOD)%MOD;
        for(int i=y+1;i<=tot&&prim[i]*prim[i]<=x;i++){
            ll pe=prim[i];
            for(int e=1;pe<=x;e++,pe=pe*prim[i]){
                ll xx=pe%MOD;
               ans=(ans+dp[e][0]*(S(x/pe,i)+(e!=1)))%MOD;
            }
        }
        return ans%MOD;
    }
    void ini(ll a,ll M){
        cntm=0;tot=0;
        n=a;
        qn=sqrt(n);
        MOD=M;
        mark.resize(qn+10);
        id1.resize(qn+10);
        id2.resize(n/qn+10);
        valm.resize(qn+n/qn+20);
        gx.resize(valm.size());
        prim.push_back(1);
        for(int i=2;i<=qn;i++){
            if(!mark[i])prim.push_back(i),tot++;
            for(int j=1;j<prim.size()&&i*prim[j]<=qn;j++){
                mark[i*prim[j]]=1;
                if(i%prim[j]==0)break;
            }
        }
        prex.resize(tot+10);pref.resize(tot+10);
        for(int i=1;i<=tot;i++){
            pref[i]=(pref[i-1]+num1)%MOD;//原函数
            prex[i]=(prex[i-1]+1)%MOD;//x
        }
        for(ll i=1,j;i<=n;i=j+1) {
            j=n/(n/i);
            ll w=n/i;valm[++cntm]=w;
            gx[cntm]=(w-1+MOD)%MOD;
            if(w<=qn) id1[w]=cntm;
            else id2[n/w]=cntm;
        }
        // for(int i=1;i<=cntm;i++)cout<<valm[i]<<" "<<gx[i]<<"\n";
        // cout<<"-------------------\n";
        for(int i=1;i<=tot;++i){
            for(int j=1;j<=cntm&&prim[i]*prim[i]<=valm[j];++j){
                ll p=getid(valm[j]/prim[i]);//定位p的坐标
                gx[j]=(gx[j]-1*(gx[p]-prex[i-1]%MOD+MOD)%MOD+MOD)%MOD;
            }
            // cout<<i<<"-------------------\n";
            // for(int i=1;i<=cntm;i++)cout<<valm[i]<<" "<<gx[i]<<"\n";
        }
    }
};

void pre(){
    for(int i=0;i<=34;i++)dp[i][0]=dp[i][1]=0;
    dp[0][1]=1;
    for(int i=1;i<=k;i++){
        for(int j=34;j>=0;j--){
            dp[j][0]=dp[j][1];
            for(int x=1;j-x*a[i]>=0;x++){
                dp[j][0]=(dp[j][0]+dp[j-x*a[i]][0])%mod;
                dp[j][1]=(dp[j][1]+dp[j-x*a[i]][1])%mod;
            }
        }
    }
}

void solve(){
    // ll n;
    // cin>>n;

    // cout<<(mm.S(n,0)+1)%mod<<"\n";
    // cout<<inv(2);
    cin>>n;
    pre();
    min_25 mm;
    mm.ini(n,mod);
    cout<<mm.gx[1]<<"\n";
}

signed main(){
    freopen("in","r",stdin);
    freopen("out","w",stdout);
    ios::sync_with_stdio(0);
    cin.tie(0);
    int t=1;
    // cin>>t;
    while(t--)solve();
    return 0;
}
/*
166666668   6^-1
500000004   2^-1
*/
