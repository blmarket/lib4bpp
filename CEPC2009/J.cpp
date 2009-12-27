#include <iostream>
#include <algorithm>
#include <cstring>
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

int n,m;
VVI edge;
VI matcher;
vector<bool> visit;

bool go(int s,int e)
{
	if(visit[s]) return false;
	visit[s]=true;
	if(s==e) return true;

	for(int i=0;i<size(edge[s]);i++) if(edge[s][i] != matcher[s])
	{
		if(go(matcher[edge[s][i]],e)) return true;
	}
	return false;
}

bool findcycle(int a)
{
	for(int i=0;i<edge[a].size();i++)
	{
		if(edge[a][i] == matcher[a]) continue;
		if(go(matcher[edge[a][i]],a)) return true;
	}
	return false;
}

bool findmatch(int a)
{
	if(visit[a]) return false;
	visit[a]=true;
	for(int i=0;i<size(edge[a]);i++)
	{
		int nn = edge[a][i];
		if(matcher[nn] == -1 || findmatch(matcher[nn]))
		{
			matcher[nn] = a;
			matcher[a] = nn;
			return true;
		}
	}
	return false;
}

void process(void)
{
	scanf("%d %d",&n,&m);
	edge = VVI(n);
	matcher = VI(n,-1);
	for(int i=0;i<m;i++)
	{
		int a,b;
		scanf("%d %d",&a,&b);
		a--;b--;
		edge[a].pb(b);
		edge[b].pb(a);
	}

	for(int i=0;i<n;i++)
	{
		if(matcher[i] != -1) continue;
		visit = vector<bool>(n,false);
		if(findmatch(i) == false)
		{
			printf("NO\n");
			return;
		}
	}

	for(int i=0;i<n;i++)
	{
		visit = vector<bool>(n,false);
		if(findcycle(i))
		{
			printf("NO\n");
			return;
		}
	}

	printf("YES\n");
	for(int i=0;i<n;i++)
	{
		if(i < matcher[i])
		{
			printf("%d %d\n",i+1,matcher[i]+1);
		}
	}
}

int main(void)
{
	int T;
	scanf("%d",&T);
	for(int i=0;i<T;i++)
		process();
	return 0;
}

