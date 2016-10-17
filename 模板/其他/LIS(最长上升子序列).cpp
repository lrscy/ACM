#include<cstdio>
#include<algorithm>
using namespace std;

int n, a[20010];
int c[20010];
int len = 0;

int find( int x ) {
    int l = 1, r = len, mid;
    while( l <= r ) {
        mid = ( l + r ) >> 1;
        if( x > c[mid] ) l = mid + 1; //���������У��ͱ�ʾx������ô���Ǵ���
        else r = mid - 1;
    }
    return l;
}

int main() {
    scanf( "%d", &n );
    for( int i = 1; i <= n; i++ )
        scanf( "%d", &a[i] );
    for( int i = 1; i <= n; i++ ) {
        int k = find( a[i] );
        c[k] = a[i];
        len = max( len, k );
    }
    printf( "%d", len );
    return 0;
}
