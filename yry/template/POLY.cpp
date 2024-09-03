#include <bits/stdc++.h>

using namespace std;
using ll = long long;
using C=complex<double>;
using i128=__int128;

const int N=4100001;

double PI=acos(-1);
int rev[N];

vector<ll> f,g;

ll qpow(ll a,ll b,ll mod){
    ll ret=1;
    for(;b;b>>=1,a=a*a%mod)if(b&1)ret=ret*a%mod;
    return ret;        
}

struct MINT{
    const static ll p1=469762049,p2=998244353,p3=1004535809,g1=3,g2=3,g3=3,invg1=156587350,invg2=332748118,invg3=334845270;
    ll x1,x2,x3;
    MINT(ll a=0):x1(a%p1),x2(a%p2),x3(a%p3){};
    MINT(ll a,ll b,ll c):x1(a%p1),x2(b%p2),x3(c%p3){};
    MINT inv()const{
        return MINT(qpow(x1,p1-2,p1),qpow(x2,p2-2,p2),qpow(x3,p3-2,p3));
    }
    MINT pow(ll b)const{
        return MINT(qpow(x1,b,p1),qpow(x2,b,p2),qpow(x3,b,p3));
    }
    ll CRT(ll p){
        i128 A=p1,B=p2,C=p3,X1=x1,X2=x2,X3=x3;
        i128 X4=X1+((X2-X1)%B+B)%B*qpow(A,B-2,B)%B*A;
        i128 K4=((X3-X4)%C+C)*qpow(A*B%C,C-2,C);
        return (X4+K4*A*B)%(A*B*C)%p;
    }
    static MINT getw(ll n,bool inv=false){
        return MINT(qpow(inv?invg1:g1,(p1-1)/n,p1),qpow(inv?invg2:g2,(p2-1)/n,p2),qpow(inv?invg3:g3,(p3-1)/n,p3));
    }
    MINT operator+(const MINT &a)const{
        ll y1=x1+a.x1,y2=x2+a.x2,y3=x3+a.x3;
        if(y1>=p1)y1-=p1;
        if(y2>=p2)y2-=p2;
        if(y3>=p3)y3-=p3;
        return MINT(y1,y2,y3);
    }
    MINT operator-(const MINT &a)const{
        ll y1=x1-a.x1,y2=x2-a.x2,y3=x3-a.x3;
        if(y1<0)y1+=p1;
        if(y2<0)y2+=p2;
        if(y3<0)y3+=p3;
        return MINT(y1,y2,y3);
    }
    MINT operator*(const MINT &a)const{
        return MINT(x1*a.x1%p1,x2*a.x2%p2,x3*a.x3%p3);
    }
    MINT operator/(const MINT &a)const{
        return *this*a.inv();
    }
    MINT operator+=(const MINT &a){
        return *this=*this+a;
    }
    MINT operator-=(const MINT &a){
        return *this=*this-a;
    }   
    MINT operator*=(const MINT &a){
        return *this=*this*a;
    }
    MINT operator/=(const MINT &a){
        return *this=*this/a;
    }
    bool operator==(const MINT &a)const{
        return x1==a.x1&&x2==a.x2&&x3==a.x3;
    }
    bool operator!=(const MINT &a)const{
        return x1!=a.x1||x2!=a.x2||x3!=a.x3;
    }
    MINT operator-()const{
        return MINT(p1-x1,p2-x2,p3-x3);
    }

};

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
    ll& operator[](const int &i){return x[i];}
};
poly operator*(poly a,poly b);
poly operator-(const poly &a,const poly &b);
poly operator+(const poly &a,const poly &b);
pair<poly,poly> operator/(poly a,poly b);
poly operator*(poly a,ll b);
poly operator*(ll a,poly b);

namespace POLY{
    const ll p=998244353,g=3,invg=332748118;
    vector<ll> vinv;
    void getrev(int s){
        for(int i=0;i<(1<<s);i++){
            rev[i]=((rev[i>>1]>>1)|((i&1)<<(s-1)));
        }
    }
    void mtt(vector<MINT> &a,int s,bool inv){
        getrev(s);
        for(int i=0;i<(1<<s);i++){
            if(i<rev[i])swap(a[i],a[rev[i]]);
        }
        for(int h=1;h<=s;h++){
            int n=1<<h;
            MINT t=1,w=MINT::getw(n,inv);
            for(int i=0;i<(1<<s);i+=n){
                t=1;
                for(int j=i;j<i+(n>>1);j++){
                    MINT tmp=t*a[j+(n>>1)];
                    a[j+(n>>1)]=a[j]-tmp;
                    a[j]=a[j]+tmp;
                    t=t*w;
                }
            }
        }
        if(inv){
            MINT invs=MINT(1<<s).inv();
            for(int i=0;i<(1<<s);i++){
                a[i]=a[i]*invs;
            }
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
            ret=ret*(2 - a.resize(i<<1)*ret);
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
    vector<poly> Q;
    poly MulT(poly a,poly b){
        int n=a.x.size(),m=b.x.size();
        reverse(b.x.begin(),b.x.end());
        b=a*b;
        for(int i=0;i<n;++i) a[i]=b[i+m-1];
        return a;
    }
    void MPinit(poly &a,int u,int cl,int cr){
        if(cl==cr){
            Q[u].x.resize(2);
            Q[u][0]=1,Q[u][1]=POLY::p-a[cl];
            return;
        }
        int mid=cl+cr>>1;
        MPinit(a,u<<1,cl,mid);MPinit(a,u<<1|1,mid+1,cr);
        Q[u]=Q[u<<1]*Q[u<<1|1];
    }
    void MPcal(int u,int cl,int cr,poly f,poly &g){
        f.x.resize(cr-cl+1);
        if(cl==cr){
            g[cl]=f[0];
            return;
        }
        int mid=cl+cr>>1;
        MPcal(u<<1,cl,mid,MulT(f,Q[u<<1|1]),g);
        MPcal(u<<1|1,mid+1,cr,MulT(f,Q[u<<1]),g);
    }
    poly Multipoints(poly f,poly a,int n){
        f.x.resize(n+1),a.x.resize(n);
        poly v;
        v.x.resize(n);
        Q.resize(n<<2);
        MPinit(a,1,0,n-1);
        MPcal(1,0,n-1,MulT(f,POLY::inv(Q[1],n+1)),v);
        return v;
    }
};
poly operator*(poly a,poly b){
    //单模
    ll al=a.x.size(),bl=b.x.size(),cl=al+bl-1;
    int s=0;
    while((1<<s)<cl)s++;
    a.x.resize(1<<s,0),b.x.resize(1<<s,0);
    POLY::ntt(a.x,s,0);
    POLY::ntt(b.x,s,0);
    for(int i=0;i<(1<<s);i++)a.x[i]=a.x[i]*b.x[i]%POLY::p;
    POLY::ntt(a.x,s,1);
    a.x.resize(cl);
    return move(a);
    //任意模数 读到POLY::mp
    // ll al=a.x.size(),bl=b.x.size(),cl=al+bl-1;
    // vector<MINT> A(a.x.begin(),a.x.end()),B(b.x.begin(),b.x.end());
    // int s=0;
    // while((1<<s)<cl)s++;
    // A.resize(1<<s);
    // B.resize(1<<s);
    // POLY::mtt(A,s,0);
    // POLY::mtt(B,s,0);
    // for(int i=0;i<(1<<s);i++)A[i]=A[i]*B[i];
    // POLY::mtt(A,s,1);
    // a.x.resize(cl);
    // for(int i=0;i<cl;i++)a.x[i]=A[i].CRT(POLY::p);
    // return move(a);
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
    ios::sync_with_stdio(false);
    cin.tie(0);
    // freopen("aa.in", "r", stdin);
    // freopen("aa.out", "w", stdout);
    int n,m;
    cin>>n>>m;
    ++n;
    poly x,y;
    x.x.resize(n);y.x.resize(m);
    for(int i=0;i<n;++i) cin>>x[i];
    for(int i=0;i<m;++i) cin>>y[i];
    auto res=POLY::Multipoints(x,y,max(n,m));
    for(int i=0;i<m;++i) cout<<res[i]<<"\n";
    return 0;
}