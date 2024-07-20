#include <bits/stdc++.h>
using namespace std;
using ll=long long;
using pisi=pair<int,int>;
using tup=tuple<int,int,int>;
constexpr int N=2e5+10;
int n,q,a[N];
int SUM[N<<5],L[N<<5],R[N<<5],VER[N+1],id=0;
int build(int l,int r){
    int root=id++,mid=(l+r)/2;
    SUM[root]=0;
    if(l<r){
        L[root]=build(l,mid);
        R[root]=build(mid+1,r);
    }
    return root;
}
int update(int pre,int l,int r,int x){
    int root=id++,mid=(l+r)/2;
    L[root]=L[pre];R[root]=R[pre];SUM[root]=SUM[pre]+1;
    if(l<r){
        if(x<=mid)L[root]=update(L[pre],l,mid,x);
        else R[root]=update(R[pre],mid+1,r,x);
    }
    return root;
}
int query_(int node,int l,int r,int x,int y){
    if(x<=l&&y>=r)return SUM[node];
    int mid=(l+r)/2,ret=0;
    if(x<=mid)ret+=query_(L[node],l,mid,x,y);
    if(y>mid)ret+=query_(R[node],mid+1,r,x,y);
    return ret;
}
int query_k(int x, int y, int l, int r, int k)
{
    if (l >= r) return l;
    int tmp = SUM[L[y]] - SUM[L[x]], mid = (l + r) / 2;
    if (tmp >= k) return query_k(L[x], L[y], l, mid, k);
    else return query_k(R[x], R[y], mid + 1, r, k - tmp);
}
int query(int l,int r,int x,int y){
    if(l>r||x>y)return 0;
    return query_(VER[r],1,n,x,y)-query_(VER[l-1],1,n,x,y);
}
int main(){
    return 0;
}