struct DSU{
    std::vector<int> fa,size,st;
    DSU( int n ){
        fa.resize( n + 1 );
        size.resize( n + 1, 1);
        for( int i = 1 ; i <= n ; i ++ ) fa[ i ] = i;
    }
    int find_fa( int x ){
        while( x != fa[ x ] ) x = fa[ x ];
        return x;
    }
    bool merge( int x, int y ){
        if( find_fa( x ) == find_fa( y ) ) return 0;
        if( size[ x ] > size[ y ] ) std::swap( x, y );
        st.push_back( x );
        fa[ x ] = y;
        size[ y ] += size[ x ];
        return 1;
    }
    void rollback(){
        if( st.empty() ) assert( 1==0 );
        int x = st.back();st.pop_back();
        size[ fa[ x ] ] -= size[ x ];
        fa[ x ] = x;
    }
};