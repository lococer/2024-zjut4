#include <iostream>
#include <stack>
#include <algorithm>
#include <set>

using namespace std;
typedef long long ll;
typedef pair<ll, ll> pis;

class worker{
    public:
    int ltr,pold,rtl,pnew,i;
    worker()=default;
    worker(int a,int b,int c,int d,int e):ltr(a),pold(b),rtl(c),pnew(d),i(e){};
    friend bool operator<(const worker& aa,const worker& bb){
        return (aa.ltr+aa.rtl>bb.ltr+bb.rtl)||(aa.ltr+aa.rtl==bb.ltr+bb.rtl&&aa.i>bb.i);
    }
    friend bool operator>(const worker& aa,const worker& bb){
        return (aa.ltr+aa.rtl<bb.ltr+bb.rtl)||(aa.ltr+aa.rtl==bb.ltr+bb.rtl&&aa.i<bb.i);
    }
    friend bool operator==(const worker& aa,const worker& bb){
        return (aa.ltr+aa.rtl==bb.ltr+bb.rtl&&aa.i==bb.i);
    }
};

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    worker w1(0,0,0,0,0),w2(0,0,0,0,2);
    set<worker> dl;
    dl.insert(w1);
    return 0;
}