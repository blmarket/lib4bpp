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

template<typename T> int size(const T &a) { return a.size(); }

int n,m,s,e;
vector<PII> lights;
vector<vector<PII> > edge;
vector<int> mint;

int dijk(int s,int e)
{
	mint.clear();
	mint.resize(n,-1);
	queue<PII> Q;
	Q.push(mp(s,5));
	mint[s]=5;

	int ret = -1;

	while(!Q.empty())
	{
		int pos = Q.front().first;
		int tt = Q.front().second;
		Q.pop();
		if(mint[pos] != tt) continue;
		for(int i=0;i<edge[pos].size();i++)
		{
			int npos = edge[pos][i].first;
			int et = tt + edge[pos][i].second;

			if(npos == e)
			{
				if(ret < 0 || ret > et) ret = et;
			}

			int lt = et % lights[npos].first;
			if(lt >= lights[npos].second)
			{
				et = et-lt+lights[npos].first+5;
			}

			if(mint[npos] < 0 || mint[npos] > et)
			{
				mint[npos] = et;
				Q.push(mp(npos,et));
			}
		}
	}

	return ret;
}

bool process(int tcase)
{
	scanf("%d %d %d %d",&n,&m,&s,&e);
	if(n==0 && m==0 && s==0 && e==0) return false;
	lights.resize(n);
	edge.clear();
	edge.resize(n);
	for(int i=0;i<n;i++)
	{
		int g,y,r;
		scanf("%d %d %d",&g,&y,&r);
		lights[i] = mp(g+y+r,g+y);
	}

	for(int i=0;i<m;i++)
	{
		int s,e,t;
		scanf("%d %d %d",&s,&e,&t);
		edge[s].pb(mp(e,t));
		edge[e].pb(mp(s,t));
	}

	int tt = dijk(s,e);
	printf("%d:%02d\n",tt/60,tt%60);
	return true;
}

int main(void)
{
	for(int i=1;;i++)
    {
        if(!process(i)) break;
    }
	return 0;
}

