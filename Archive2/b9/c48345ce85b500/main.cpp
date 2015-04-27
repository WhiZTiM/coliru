#include <iostream>

using namespace std ;

int main ()
    {
    int V1,V2,V3,V4;
	cin >> V1 >> V2 >> V3 >> V4 ;
	if ((V1<V2+V3 || V1<V2+V4 || V1<V3+V4) || (V2<V1+V3 || V2<V1+V4 || V2<V3+V4) || (V3<V1+V2 || V3<V1+V4 || V3<V2+V4) || (V4<V1+V2 || V4<V1+V3 || V4<V2+V3)) {
		cout << "S" ;
	}else {
		cout << "N" ;
	}
	return 0 ;
	}