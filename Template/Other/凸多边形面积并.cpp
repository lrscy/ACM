#include <cmath>
#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;

const int maxn = 505;
const int maxm = 5005;
const double eps = 1e-8;
const double PI = acos(-1.0);

inline int dcmp(double a) {
	return a < -eps ? -1 : a > eps;
}

struct Point {
	double x, y;
	Point(){}
	Point(double a, double b): x(a), y(b){}
	bool operator < (const Point p) const {
		return y+eps < p.y || (y < p.y+eps && x+eps < p.x);
	}
	bool operator == (const Point p) const {
		return !dcmp(x-p.x) && !dcmp(y-p.y);
	}
	Point operator + (const Point p) const {
		return Point(x+p.x, y+p.y);
	}
	Point operator - (const Point p) const {
		return Point(x-p.x, y-p.y);
	}
	Point operator * (const double p) const {
		return Point(x*p, y*p);
	}
	Point operator / (const double p) const {
		return Point(x/p, y/p);
	}
	double operator * (const Point p) const {
		return x*p.y - y*p.x;
	}
	double operator / (const Point p) const {
		return x*p.x + y*p.y;
	}
	void input() { scanf("%lf %lf", &x, &y); }
};

struct Polygon {
	int n;
	Point p[maxn];
	Point& operator [] (const int i) { return p[i]; }
	void init() {
		double x1, x2, y1, y2;
		n = 4;
		for(int i = 0; i < 4; i++) p[i].input();
	}
	double Area() {
		double sum = 0;
		for(int i = 1; i < n-1; i++)
			sum += (p[i]-p[0]) * (p[i+1]-p[0]);
		return sum / 2.0;
	}
};

struct Polygons {
	int n;
	Polygon py[maxn];
	std::pair <double, int> c[maxm];
	void init() { n = 0; }
	void push(Polygon p) {
		p[p.n] = p[0];
		py[n++] = p;
	}
	double seg(Point p, Point p1, Point p2) {
		if(!dcmp(p1.x-p2.x))
			return (p.y-p1.y) / (p2.y-p1.y);
		return (p.x-p1.x) / (p2.x-p1.x);
	}
	double PolyUnion() {
		int d, r, ta, tb;
		double s, w, z, sum, tc, td;
		sum = 0;
		for(int i = 0; i < n; i++) {
			for(int ii = 0; ii < py[i].n; ii++) {
				r = 0;
				c[r++] = make_pair(0.0, 0);
				c[r++] = make_pair(1.0, 0);
				for(int j = 0; j < n; j++) {
					if(i == j) continue;
					for(int jj = 0; jj < py[j].n; jj++) {
						ta = dcmp((py[i][ii+1]-py[i][ii])*(py[j][jj]-py[i][ii]));
						tb = dcmp((py[i][ii+1]-py[i][ii])*(py[j][jj+1]-py[i][ii]));
						if(!ta && !tb) {
							if((py[j][jj+1]-py[j][jj])/(py[i][ii+1]-py[i][ii]) > 0 && j < i) {
								c[r++] = make_pair(seg(py[j][jj], py[i][ii], py[i][ii+1]), 1);
								c[r++] = make_pair(seg(py[j][jj+1], py[i][ii], py[i][ii+1]), -1);
							}
						} else if(ta >= 0 && tb < 0) {
							tc = (py[j][jj+1]-py[j][jj]) * (py[i][ii]-py[j][jj]);
							td = (py[j][jj+1]-py[j][jj]) * (py[i][ii+1]-py[j][jj]);
							c[r++] = make_pair(tc/(tc-td), 1);
						} else if(ta < 0 && tb >= 0) {
							tc = (py[j][jj+1]-py[j][jj]) * (py[i][ii]-py[j][jj]);
							td = (py[j][jj+1]-py[j][jj]) * (py[i][ii+1]-py[j][jj]);
							c[r++] = make_pair(tc/(tc-td), -1);
						}
					}
				}
				std::sort(c, c+r);
				z = std::min(std::max(c[0].first, 0.0), 1.0);
				d = c[0].second;
				s = 0;
				for(int j = 1; j < r; j++) {
					w = std::min(std::max(c[j].first, 0.0), 1.0);
					if(!d) s += w - z;
					d += c[j].second;
					z = w;
				}
				sum += (py[i][ii]*py[i][ii+1]) * s;
			}
        }
		return sum / 2.0;
	}
};

Polygons P;
Polygon pp;

int main() {
	int n;
	double area, sum = 0;
	scanf("%d",&n);
	P.init();
	for(int i = 0; i < n; i++) {
		pp.init();
		area = pp.Area();
		if(area < 0) {
			for(int j = 0,k = pp.n-1; j < k; j++, k--)
				std::swap(pp[j], pp[k]);
			area = -area;
		}
		sum += area;
		P.push(pp);
	}
	printf("%.10f\n", sum / P.PolyUnion());
	return 0;
}
