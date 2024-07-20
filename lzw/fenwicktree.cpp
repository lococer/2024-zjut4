template<typename T>
struct fenwicktree{
    std::vector<T> tr;
    fenwicktree(int n){tr.resize((n+10)<<1);}
    int lowbit(int x){return x&-x;}
    void add(int p,T x){for(;p<tr.size();p+=lowbit(p))tr[p]+=x;}
    int ask(int p){T ans=0;for(;p;p-=lowbit(p))ans+=tr[p];return ans;}
    int ask(int l,int r){ return ask(r)-ask(l-1);}
};
