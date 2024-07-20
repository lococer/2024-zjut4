#include <bits/stdc++.h>

using namespace std;
using ll = long long;
using C=complex<double>;


const int N=4100001;

double PI=acos(-1);
int rev[N];

vector<ll> f,g;

struct poly{
    vector<ll> x;
    poly()=default;
    poly(const vector<ll> &a):x(a){};
    poly(ll a):x(1,a){};
    poly resize(int n)const{
        vector<ll> ret(n);
        for(int i=0;i<min(n,(int)x.size());i++)ret[i]=x[i];
        return move(poly(ret));
    }
};
poly operator*(const poly &a,const poly &b);
poly operator-(const poly &a,const poly &b);
poly operator+(const poly &a,const poly &b);
pair<poly,poly> operator/(poly a,poly b);
poly operator*(poly a,ll b);
poly operator*(ll a,poly b);



ll qpow(ll a,ll b,ll mod){
    ll ret=1;
    for(;b;b>>=1,a=a*a%mod)if(b&1)ret=ret*a%mod;
    return ret;        
}

namespace POLY{
    const ll p=998244353,g=3,invg=332748118;
    vector<ll> vinv;
    void getrev(int s){
        for(int i=0;i<(1<<s);i++){
            rev[i]=((rev[i>>1]>>1)|((i&1)<<(s-1)));
        }
    }
    void fft(C *a,int s,bool inv){
        getrev(s);
        for(int i=0;i<(1<<s);i++){
            if(i<rev[i])swap(a[i],a[rev[i]]);
        }
        for(int h=1;h<=s;h++){
            int n=1<<h;
            C t(1,0),w(cos(2*PI/n),sin(2*PI/n));
            if(inv)w=C(cos(2*PI/n),-sin(2*PI/n));
            for(int i=0;i<(1<<s);i+=n){
                t=C(1,0);
                for(int j=i;j<i+(n>>1);j++){
                    C tmp=t*a[j+(n>>1)];
                    a[j+(n>>1)]=a[j]-tmp;
                    a[j]=a[j]+tmp;
                    t=t*w;
                }
            }
        }
        if(inv){
            for(int i=0;i<(1<<s);i++){
                a[i]/=(1<<s);
            }
        }
    }
    void ntt(vector<ll> &a,int s,bool inv){
        getrev(s);
        for(int i=0;i<(1<<s);i++){
            if(i<rev[i])swap(a[i],a[rev[i]]);
        }
        for(int h=1;h<=s;h++){
            int n=1<<h;
            ll t=1,w=qpow(inv?invg:g,(p-1)/n,p);
            for(int i=0;i<(1<<s);i+=n){
                t=1;
                for(int j=i;j<i+(n>>1);j++){
                    ll tmp=t*a[j+(n>>1)]%p;
                    a[j+(n>>1)]=((a[j]-tmp)%p+p)%p;
                    a[j]=(a[j]+tmp)%p;
                    t=t*w%p;
                }
            }
        }
        if(inv){
            ll invs=qpow(1<<s,p-2,p);
            for(int i=0;i<(1<<s);i++){
                a[i]=a[i]*invs%p;
            }
        }
    }
    poly inv(const poly &a,int k){
        poly ret(vector<ll>(1,qpow(a.x.front(),p-2,p)));
        for(int i=1;i<k;i<<=1){
            ret=ret*(2-a.resize(i<<1)*ret);
            ret.x.resize(i<<1);
        }
        ret.x.resize(k);
        return ret;
    }
    poly d(poly a){
        for(int i=0;i+1<a.x.size();i++){
            a.x[i]=a.x[i+1]*(i+1)%p;
        }
        a.x.pop_back();
        return a;
    }
    poly i(poly a){
        a.x.push_back(0);
        for(int i=a.x.size()-1;i;i--){
            a.x[i]=a.x[i-1]*qpow(i,p-2,p)%p;
        }
        a.x[0]=0;
        return a;
    }
    poly ln(poly a,int k){//a0=1
        a.x.resize(k);
        return i((d(a)*inv(a,k)).resize(k)).resize(k);
    }
    poly exp(const poly &a,int k){//a0=1
        poly ret(1);
        for(int i=1;i<k;i<<=1){
            ret=ret*(1+a.resize(i<<1)-ln(ret,i<<1));
            ret.x.resize(i<<1);
        }
        ret.x.resize(k);
        return ret;
    }
};
poly operator*(const poly &a,const poly &b){
    ll al=a.x.size(),bl=b.x.size(),cl=al+bl-1;
    int s=0;
    while((1<<s)<cl)s++;
    auto A=a.resize(1<<s),B=b.resize(1<<s);
    poly c(vector<ll>(1<<s));
    POLY::ntt(A.x,s,0);
    POLY::ntt(B.x,s,0);
    for(int i=0;i<(1<<s);i++)c.x[i]=A.x[i]*B.x[i]%POLY::p;
    POLY::ntt(c.x,s,1);
    c.x.resize(cl);
    return move(c);
}
poly operator-(const poly &a,const poly &b){
    ll al=a.x.size(),bl=b.x.size(),cl=max(al,bl);
    poly c=poly(vector<ll>(cl));
    for(int i=0;i<cl;i++){
        if(i<al)c.x[i]+=a.x[i];
        if(i<bl)c.x[i]-=b.x[i];
        c.x[i]=(c.x[i]+POLY::p)%POLY::p;
    }
    return move(c);
}
poly operator*(poly a,ll b){
    poly c(a);
    for(auto &aa:c.x)aa=aa*b%POLY::p;
    return move(c);
}
poly operator*(ll a,poly b){
    poly c(b);
    for(auto &aa:c.x)aa=aa*a%POLY::p;
    return move(c);
}
poly operator+(const poly &a,const poly &b){
    ll al=a.x.size(),bl=b.x.size(),cl=max(al,bl);
    poly c=poly(vector<ll>(cl));
    for(int i=0;i<cl;i++){
        if(i<al)c.x[i]+=a.x[i];
        if(i<bl)c.x[i]+=b.x[i];
        c.x[i]%=POLY::p;
    }
    return move(c);
}
pair<poly,poly> operator/(poly a,poly b){
    int n=a.x.size(),m=b.x.size();
    if(n<m)return make_pair(poly(vector<ll>(1,0)),move(a));
    reverse(a.x.begin(),a.x.end());
    reverse(b.x.begin(),b.x.end());
    poly c=a*(POLY::inv(b,n-m+1));
    c.x.resize(n-m+1);
    reverse(c.x.begin(),c.x.end());
    reverse(a.x.begin(),a.x.end());
    reverse(b.x.begin(),b.x.end());
    poly r=a-c*b;
    r.x.resize(m-1,0);
    return make_pair(move(c),move(r));
}
poly operator<<(poly a,int b){
    poly c(a);
    for(int i=0;i<c.x.size();i++){
        if(i+b<c.x.size())c.x[i]=c.x[i+b];
        else c.x[i]=0;
    }
    c.x.resize(max((int)c.x.size()-b,1));
    return move(c);
}
poly operator>>(poly a,int b){
    poly c(a);
    c.x.resize(c.x.size()+b);
    for(int i=(int)c.x.size()-1;i>=0;i--){
        if(i-b>=0)c.x[i]=c.x[i-b];
        else c.x[i]=0;
    }
    return move(c);
}

signed main()
{
    // ios::sync_with_stdio(false);
    // cin.tie(0);
    // freopen("aa.in", "r", stdin);
    // freopen("aa.out", "w", stdout);
    ll n;
    ll k=0,k1=0;
    cin>>n;
    string s;
    cin>>s;
    for(auto c:s){
        k=(k*10%POLY::p+c-'0')%POLY::p;
        k1=(k1*10%998244352ll+c-'0')%998244352ll;
    }
    f.resize(n);
    int kk=0,ak=0;
    for(int i=0;i<n;i++){
        cin>>f[i];
        if(f[i]>0&&ak==0){
            kk=i;
            ak=f[i];
        }
    }
    poly F(f);
    F=(F<<kk)*qpow(ak,POLY::p-2,POLY::p);
    auto G=(POLY::exp(k*POLY::ln(F,n),n)*qpow(ak,k1,POLY::p))>>min(kk*k1%998244352ll,n*2ll);
    for(int i=0;i<n;i++)cout<<G.x[i]<<" ";
    return 0;
}