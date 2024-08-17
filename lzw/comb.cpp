struct COMB{
    std::vector<int> fac,invfac;
    COMB( int n ){
        fac.resize( n + 100 );
        invfac.resize( n + 100 );
        fac[ 0 ] = 1;
        for( int i = 1 ; i <= n ; i ++ ) fac[ i ] = fac[ i - 1 ] * i % MOD;
        invfac[ n ] = inv( fac[ n ] );
        for( int i = n - 1 ; i >= 0 ; i -- ) invfac[ i ] = invfac[ i + 1 ] * ( i + 1 ) % MOD;
    }
    int C( int m, int n ){
        if( n > m ) return 0;
        return fac[ m ] * invfac[ n ] % MOD * invfac[ m - n ] % MOD;
    }
    int A( int m, int n ){
        if( n > m ) return 0;
        return fac[ m ] * invfac[ m - n ] % MOD;
    }
}comb( 1E6 );