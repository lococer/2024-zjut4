// geometry
struct Geo{
	struct Point{
		int x, y;
	};
	int dis2( Point p1, Point p2 ){
		int x = p1.x - p2.x;
		int y = p1.y - p2.y;
		return x * x + y * y;
	}
	double dis( Point p1, Point p2 ){
		return sqrt( dis2( p1, p2 ) ) ;
	}

	int cross( Point p1, Point p2, Point p3 ){
		int x1 = p2.x - p1.x, x2 = p3.x - p2.x;
		int y1 = p2.y - p1.y, y2 = p3.y - p2.y;
		return x1 * y2 - x2 * y1;
	}
	// 参数从1开始，返回从1开始
	std::vector<Point> tubao( std::vector<Point> v ){
		std::sort(v.begin() + 1, v.end(), [](Point p1, Point p2){
			if( p1.x != p2.x ) return p1.x < p2.x;
			return p1.y < p2.y;
		});

		int size = v.size() - 1;

		std::vector<Point> st( ( size + 10 ) << 1 );// 栈
		int stp = 0;// 栈指针
		st[ ++stp ] = v[ 1 ];
		st[ ++stp ] = v[ 2 ];
		for( int i = 3 ; i <= size ; i ++ ){ // 下凸包
			while( stp >= 2 && cross( st[ stp - 1 ], st[ stp ], v[ i ] ) < 0 ) stp--;
			st[ ++stp ] = v[ i ];
		}
		int t = stp;
    	for( int i = size - 1 ; i >= 1 ; i -- ){ // 上凸包
        	while( stp > t && cross( st[ stp-1 ] , st[ stp ] , v[ i ] ) < 0 ) // while
        	stp--;
        	st[ ++stp ] = v[ i ]; 
    	}
    	double cnt = 0;
		std::vector<Point> ans( stp );
    	for( int i = 1 ; i < stp ; i ++ ){
        	// cnt += dis( st[ i ] , st[ i + 1 ] );
			ans[ i ] = st[ i ];
    	}
    	// std::cout<<std::fixed<<std::setprecision(2)<<cnt<<'\n';
		return ans;
	}

	// 获得严格凸包直径,参数从1开始
	double getd( std::vector<Point> v ){
		int size = v.size() - 1;
		v.push_back( v[ 1 ] );
		int j = 3;
		if( size == 1 ){
			return 0;
		}
		if( size == 2 ){
			return dis( v[ 1 ], v[ 2 ] );
		}
		double ans = 0;
		for( int i = 1 ; i <= size; i ++ ){
			while( cross(v[i], v[i+1], v[j]) < cross(v[i], v[i+1], v[j+1]))
				j = j %  size + 1;
			ans = std::max({ans,dis(v[i],v[j]),dis(v[i+1],v[j])});
		}
		return ans;
	}

}geo;