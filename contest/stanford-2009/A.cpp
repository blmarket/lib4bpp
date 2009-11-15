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

template<typename T> inline int size(const T &a) { return a.size(); }
template<typename T> inline bool operator<(const int &a,const vector<T> &b) { return a<b.size(); }

vector<vector<PII> > edge;

int calc(int a,int par)
{
	int ret = 0;
	bool leaf = true;
	for(int i=0;i<edge[a];i++)
	{
		int node = edge[a][i].first;
		int weight = edge[a][i].second;

		if(node == par) continue;
		leaf=false;
		ret += min(calc(node,a),weight);
	}
	if(leaf) return 1005;
	return ret;
}

bool process(void)
{
	int n,r;
	scanf("%d %d",&n,&r);
	if(n==0 && r==0) return false;
	if(n == 1)
	{
		cout << 0 << endl;
		return true;
	}
	r--;

	edge.clear();
	edge.resize(n);
	for(int i=0;i<n-1;i++)
	{
		int a,b,c;
		scanf("%d %d %d",&a,&b,&c);
		a--;b--;
		edge[a].pb(mp(b,c));
		edge[b].pb(mp(a,c));
	}

	cout << calc(r,-1) << endl;
	return true;
}

int main(void)
{
	while(process());
}

