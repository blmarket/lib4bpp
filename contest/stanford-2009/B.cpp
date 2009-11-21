#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <cmath>
#include <sstream>
#include <queue>
#include <set>
#include <map>
#include <algorithm>
#include <complex>
#include <vector>

#define mp make_pair
#define pb push_back
#define sqr(x) ((x)*(x))
#define foreach(it,c) for(typeof((c).begin()) it = (c).begin(); it != (c).end(); ++it)

using namespace std;

typedef vector<int> VI;
typedef vector<VI> VVI;
typedef vector<string> VS;
typedef pair<int,int> PII;
typedef long long LL;
typedef complex<double> Point;
typedef complex<double> Vec;

template<typename T> inline int size(const T &a) { return a.size(); }
template<typename T> inline bool operator<(const int &a,const vector<T> &b) { return a<b.size(); }

pair<Point, Point> circle_line(Point l1, Point l2, Point c1, double radius)
{
	l2 -= l1;
	l2 /= abs(l2);
	c1 -= l1;
	c1 /= l2;

	double rdiff = sqrt( sqr(radius) - sqr(c1.imag()) );
	Point t1(c1.real() + rdiff),t2(c1.real() - rdiff);
	t1 /= l2; t2 /= l2;
	t1 += l1; t2 += l1;
	return mp(t1,t2);
}

pair<double, double> circle_circle(Point p1, Point p2, double radius)
{
	Point vec = p2 - p1;
	vec /= 2;

	double rdiff = sqrt( sqr(radius) - norm(vec) );

	Point vec2(vec.imag(), -vec.real());
	vec2 *= rdiff / abs(vec2);

	Point tmp1 = vec + vec2;
	Point tmp2 = vec - vec2;

	cout << tmp1 << " " << tmp2 << endl;

	return mp(0,0);
}

Vec get90(Vec v)
{
	Vec ret(v.imag(), -v.real());
	ret /= abs(ret);
	if(ret.imag() < 0) return -ret;
	return ret;
}

int main(void)
{
	pair<Point,Point> tmp;
	tmp = circle_line(Point(0,1), Point(10,1), Point(5,4), 5);
	cout << tmp.first << " " << tmp.second << endl;
	circle_circle(Point(0,0), Point(10,0), 5);
	return 0;
}

