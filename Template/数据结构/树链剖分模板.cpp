#include <bits/stdc++.h>
using namespace std;
typedef long long LL;
const int MAXN = 10000 + 10;
const int MAXM = 1000000 + 10;
#define MID(x, y) (((x) + (y)) >> 1)

int fa[MAXN], top[MAXN], w[MAXN], son[MAXN], dep[MAXN], sz[MAXN], r[MAXN];
int a[MAXN], b[MAXN];
LL c[MAXN];
int ind[MAXN];
int t[MAXM], nt[MAXM];
int cnt1, cnt2, cnt3;
int n, m;

struct node {
    int l, r;
    int a, b;
    LL sum;
}f[MAXM];
int rt;

void dfs1( int x, int d ) {
    dep[x] = d; son[x] = 0; sz[x] = 1;
    for( int k = ind[x]; ~k; k = nt[k] ) {
        if( t[k] != fa[x] ) {
            fa[t[k]] = x;
            dfs1( t[k], d + 1 );
            sz[x] += sz[t[k]];
            if( sz[t[k]] > sz[son[x]] ) son[x] = t[k];
        }
    }
    return ;
}

void dfs2( int x, int tt ) {
    w[x] = ++cnt2; top[x] = tt;
    if( son[x] ) dfs2( son[x], tt );
    for( int k = ind[x]; ~k; k = nt[k] ) {
        if( t[k] != fa[x] && t[k] != son[x] )
            dfs2( t[k], t[k] );
    }
    return ;
}

void add( int a, int b ) {
    t[cnt1] = b; nt[cnt1] = ind[a]; ind[a] = cnt1++;
    return ;
}

void update( int x ) {
    f[x].sum = f[f[x].l].sum + f[f[x].r].sum;
}

int bt( int a, int b ) {
    int x = cnt3++;
    f[x].a = a; f[x].b = b;
    if( a < b ) {
        int mid = MID( a, b );
        f[x].l = bt( a, mid );
        f[x].r = bt( mid + 1, b );
        f[x].sum = 0;
    } else f[x].sum = 0;
    return x;
}

// Query On ST, Do not Call Directly
LL query( int x, int a, int b ) {
    if( a <= f[x].a && f[x].b <= b ) return f[x].sum;
    int mid = MID( f[x].a, f[x].b );
    LL ans = 0;
    if( a <= mid ) ans += query( f[x].l, a, b );
    if( b > mid ) ans += query( f[x].r, a, b );
    return ans;
}

//Modify Point
void update( int x, int p, int cc ) {
    if( f[x].a == f[x].b ) { f[x].sum = cc; return; }
    int mid = MID( f[x].a, f[x].b );
    if( p <= mid ) update( f[x].l, p, cc );
    else update( f[x].r, p, cc );
    update( x );
    return ;
}

//Query Segment
LL query( int x, int y ) {
    int fx = top[x], fy = top[y];
    LL sum = 0;
    while( fx != fy ) {
        if( dep[fx] < dep[fy] ) {
            swap( x, y );
            swap( fx, fy );
        }
        sum += query( rt, w[fx], w[x] );
        x = fa[top[x]];
        fx = top[x];
    }
    if( dep[x] > dep[y] ) swap( x, y );
    if( x == y ) return sum;
    return sum + query( rt, w[son[x]], w[y] );
}

int main() {
    return 0;
}
