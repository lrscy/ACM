//���������
#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>
#include <cmath>
#include <string>
#include <functional>
using namespace std;
const double eps = 1e-10;

int n;
pair<double, int> c[10000];

struct point { double x, y; } p[600][5];

int dblcmake_pair( double x ) {
    if( fabs(x) < eps )    return 0;
    return x > 0 ? 1 : -1;
}

double cross( point& p1, point& p2, point& p3 ) {
    return (p2.x-p1.x)*(p3.y-p1.y) - (p2.y-p1.y)*(p3.x-p1.x);
}

double dot( point aa, point bb ) {
    return aa.x*bb.x + aa.y*bb.y;
}

double segP( point p1, point p2, point p3 ) {
    if( dblcmake_pair(p2.x-p3.x) )
        return (p1.x-p2.x)/(p3.x-p2.x);
    else
        return (p1.y-p2.y)/(p3.y-p2.y);
}

double polyUnion() {
    int i, j, ii, jj, ta, tb, r, d;
    double z, w, s, sum, tc, td;
    point tmake_pair1, tmake_pair2;
    sum = 0;
    for( i = 0; i < n; ++i ) {
        for( ii = 0; ii < 4; ++ii ) {
            r = 0;
            c[r++] = make_pair(0., 0);
            c[r++] = make_pair(1., 0);
            for( j = 0; j < n; ++j ) if( i-j ) {
                for( jj = 0; jj < 4; ++jj ) {
                    ta = dblcmake_pair( cross(p[i][ii], p[i][ii+1], p[j][jj]) );
                    tb = dblcmake_pair( cross(p[i][ii], p[i][ii+1], p[j][jj+1]) );
                    if( !ta && !tb ) {
                        tmake_pair1.x = p[j][jj+1].x-p[j][jj].x;
                        tmake_pair1.y = p[j][jj+1].y-p[j][jj].y;
                        tmake_pair2.x = p[i][ii+1].x-p[i][ii].x;
                        tmake_pair2.y = p[i][ii+1].y-p[i][ii].y;
                        if( dblcmake_pair( dot(tmake_pair1, tmake_pair2) ) > 0 && j < i ) {
                            c[r++] = make_pair( segP(p[j][jj], p[i][ii], p[i][ii+1]), 1 );
                            c[r++] = make_pair( segP(p[j][jj+1], p[i][ii], p[i][ii+1]), -1 );
                        }
                    } else if( ta >= 0 && tb < 0 ) {
                        tc = cross(p[j][jj], p[j][jj+1], p[i][ii]);
                        td = cross(p[j][jj], p[j][jj+1], p[i][ii+1]);
                        c[r++] = make_pair(tc/(tc-td), 1);
                    } else if( ta < 0 && tb >= 0 ) {
                        tc = cross(p[j][jj], p[j][jj+1], p[i][ii]);
                        td = cross(p[j][jj], p[j][jj+1], p[i][ii+1]);
                        c[r++] = make_pair(tc/(tc-td), -1);
                    }
                }
            }
            sort(c, c+r);
            z = min(max(c[0].first, 0.), 1.);
            d = c[0].second; s = 0;
            for( j = 1; j < r; ++j ) {
                w = min(max(c[j].first, 0.), 1.);
                if( !d ) s += w-z;
                d += c[j].second;
                z = w;
            }
            tmake_pair1.x = tmake_pair1.y = 0;
            sum += cross(tmake_pair1, p[i][ii], p[i][ii+1])*s;
        }
    }
    return 0.5*sum;
}

int main() {
    int i, j;
    double area, tmake_pair;
    while( scanf("%d", &n) != EOF ) {
        area = 0;
        for( i = 0; i < n; ++i ) {
            for( j = 0; j < 4; ++j )
                scanf("%lf %lf", &p[i][j].x, &p[i][j].y);
            p[i][4] = p[i][0];
            tmake_pair = 0;
            for( j = 1; j <= 4; ++j )
                tmake_pair += p[i][j-1].x*p[i][j].y - p[i][j-1].y*p[i][j].x;
            area += fabs(tmake_pair);
            if( dblcmake_pair(tmake_pair) < 0 ) swap(p[i][1], p[i][3]);
        }
        printf("%.10lf\n", 0.5*area/polyUnion() );
    }
    return 0;
}
