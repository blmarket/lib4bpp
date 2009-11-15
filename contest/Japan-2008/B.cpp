#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <cmath>
#include <sstream>
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
typedef long long LL;

template<typename T> int size(const T &a) { return a.size(); }

bool process(void)
{
	int n,m,k;
	vector<int> cur,next;
	scanf("%d %d %d",&n,&m,&k);
	if(n==0 && m==0 && k==0) return false;
	cur.resize(1,1);
	LL ncase = 1;
	for(int i=0;i<n;i++)
	{
		ncase *= m;
		next.clear();
		next.resize(cur.size()+m);
		for(int k=0;k<m;k++)
		{
			for(int j=0;j<cur.size();j++)
			{
				next[k+1+j] += cur[j];
			}
		}
		cur.swap(next);
	}

	double ret = 0;
	for(int i=0;i<=k;i++)
	{
		double prob = (double)cur[i] / ncase;
		ret += prob;
	}
	for(int i=k+1;i<size(cur);i++)
	{
		double prob = (double)cur[i] / ncase;
		ret += prob * (i-k);
	}

	printf("%.12lf\n",ret);
	return true;
}

int main(void)
{
	while(process());
}

