#include <iostream>
#include <complex>
#include <queue>
#include <set>
#include <map>
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
typedef complex<double> point;

template<typename T> int size(const T &a) { return a.size(); }

vector<point> v1,v2;

double dot(const point &a, const point &b) { return real(conj(a) * b); }
double cross(const point &a, const point &b) { return imag(conj(a) * b); }

point reflect(const point &p, const point &about1, const point &about2)
{
    point z = p - about1;
    point w = about2 - about1;
    return conj(z / w) * w + about1;
}

double ldist(const point &p, const point &about1, const point &about2)
{
	point vec = about2 - about1;
	point pvec = p - about1;
	if(dot(pvec,vec) < -1e-12 || dot(pvec,vec) > dot(vec,vec)) return 1e12;
	point p2 = reflect(p,about1,about2);
	return abs((p-p2)/2.0);
}

void rr(vector<point> &ret)
{
	int n;
	scanf("%d",&n);
	ret.clear();
	for(int i=0;i<n;i++)
	{
		int a,b;
		scanf("%d %d",&a,&b);
		ret.pb(point(a,b));
	}
}

void process(void)
{
	rr(v1);
	rr(v2);

	double mindist = -1;
	for(int i=0;i<v1.size();i++)
	{
		for(int j=0;j<v2.size();j++)
		{
			double tmp = abs(v1[i]-v2[j]);
			if(mindist < 0 || mindist > tmp) mindist = tmp;
		}
	}

	v1.pb(v1[0]);
	v2.pb(v2[0]);
	for(int i=0;i<size(v1)-1;i++)
	{
		for(int j=0;j<size(v2)-1;j++)
		{
			double tmp = ldist(v1[i],v2[j],v2[j+1]);
			if(mindist < 0 || mindist > tmp) mindist = tmp;
			tmp = ldist(v2[j],v1[i],v1[i+1]);
			if(mindist < 0 || mindist > tmp) mindist = tmp;
		}
	}

	printf("%.8lf\n",mindist / 2.0);
}

int main(void)
{
	int n;
	scanf("%d",&n);
	for(int i=0;i<n;i++)
		process();
}

