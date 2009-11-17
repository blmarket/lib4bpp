#include <iostream>
#include <algorithm>
#include <cstdio>
#include <cstdlib>
#include <cmath>
#include <sstream>
#include <queue>
#include <set>
#include <map>
#include <vector>
#include <complex>

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

template<typename T> inline int size(const T &a) { return a.size(); }
template<typename T> inline bool operator<(const int &a,const vector<T> &b) { return a<b.size(); }

double f2;

void draw_line(Point p1,Point p2,Point px,vector<double> &ret)
{
	Point tx = px - p1;
	Point vec = p2-p1;
	tx /= vec;

	double r1,r2;
	r1 = tx.real() + tx.imag() / sqrt(f2);
	r2 = tx.real() - tx.imag() / sqrt(f2);

	if(r1 > 0 && r1 < 1.0) ret.pb(r1);
	if(r2 > 0 && r2 < 1.0) ret.pb(r2);
}

vector<Point> ptrs;
vector<double> visit;
vector<int> prev;

double getdist(const Point &a, const Point &b)
{
	return abs(b-a);
}

void btrace(int a)
{
	cout << ptrs[a] << " ";
	if(prev[a] == -1) return;
	btrace(prev[a]);
}

bool process(int tcase)
{
	int n,f;
	scanf("%d %d",&n,&f);
	if(n == 0 && f==0) return false;
	f2 = (double)(f*f)-1;

	vector<Point> vecs;

	for(int i=0;i<n+1;i++)
	{
		int a,b;
		scanf("%d %d",&a,&b);
		vecs.pb(Point(a,b));
	}

	ptrs.clear();

	for(int i=0;i<n;i++)
	{
		Point p1 = vecs[i];
		Point p2 = vecs[i+1];

		vector<double> tmp;
		tmp.clear();
		tmp.pb(0);
		tmp.pb(1);
		for(int j=0;j<n+1;j++)
			draw_line(p1,p2,vecs[j],tmp);
		sort(tmp.begin(),tmp.end());

		for(int i=0;i<size(tmp);i++)
		{
			Point tmpp = p1 * (1 - tmp[i]) + p2 * tmp[i];
//			cout << tmpp << endl;
			ptrs.pb(tmpp);
		}
	}

	visit.clear();
	visit.resize(size(ptrs),-1);
	prev.clear();
	prev.resize(size(ptrs),-1);

	priority_queue<pair<double,int> > Q;
	Q.push(mp(0,0));
	visit[0]=0;

	while(Q.empty() == false)
	{
		double dist = -Q.top().first;
		int node = Q.top().second;
		Q.pop();
		if(visit[node] < dist - 1e-9) continue;

		if(node == size(ptrs)-1)
		{
			// end
			printf("Case %d: %.3lf\n",tcase, dist);
			btrace(size(ptrs)-1);
			cout << endl;
			return true;
		}

		if(node+1 < size(ptrs))
		{
			double tdist = dist + getdist(ptrs[node],ptrs[node+1]);
			if(visit[node+1] < 0 || visit[node+1] > tdist)
			{
				visit[node+1] = tdist;
				prev[node+1] = node;
				Q.push(mp(-tdist, node+1));
			}
		}

		if(node-1 >= 0)
		{
			double tdist = dist + getdist(ptrs[node],ptrs[node-1]);
			int nnode = node-1;
			if(visit[nnode] < 0 || visit[nnode] > tdist)
			{
				visit[nnode] = tdist;
				prev[nnode] = node;
				Q.push(mp(-tdist, nnode));
			}
		}

		for(int i=0;i<size(ptrs);i++)
		{
			double tdist = dist + getdist(ptrs[node], ptrs[i]) * f;
			if(visit[i] < 0 || visit[i] > tdist)
			{
				visit[i] = tdist;
				prev[i] = node;
				Q.push(mp(-tdist, i));
			}
		}
	}

	return true;
}

int main(void)
{
	for(int i=1;;i++)
	{
		if(process(i)==false) break;
	}
	return 0;
}

