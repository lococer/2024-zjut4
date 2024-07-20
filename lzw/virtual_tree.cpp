int st[ N ];
void build( std::vector<int> &a ){
    std::sort( a.begin(), a.end(), cmp );
    int top = 1;
    st[ top ] = 1;
    for( auto i : a ){
        int lca = LCA( i, st[ top ] );
        if( lca != st[ top ] ){
            while( dfn[ lca ] < dfn[ st[ top - 1 ] ] ){
                g2.add_e( st[ top-1 ], st[top ], getcost( st[ top - 1 ], st[ top ] ) );
                top--;
            }
            if( dfn[ lca ] > dfn[ st[ top - 1 ] ] ){
                g2.add_e( lca, st[ top ], getcost( lca, st[ top ] ) );
                st[ top ] = lca;
            }else{
                g2.add_e( lca, st[ top ], getcost( lca, st[ top ] ) );
                top--;
            }
        }
        st[ ++top ] = i;
    }
    for( int i = 1 ; i < top ; i ++ ){
        g2.add_e( st[ i ], st[ i + 1 ], getcost( st[ i ], st[ i + 1 ]) );
    }
}