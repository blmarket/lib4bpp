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

set<PII> visit;

bool process(void)
{
	int n;
	scanf("%d",&n);
	if(n==0) return false;
	vector<int> V(n);
	for(int i=0;i<n;i++)
		scanf("%d",&V[i]);

	queue<pair<PII,int> > Q;
	visit.clear();
	Q.push(mp(mp(0,1),0));

	if(V.size() == 2)
	{
		cout << 0 << endl;
		return true;
	}

	while(!Q.empty())
	{
		PII pos = Q.front().first;
		int turn = Q.front().second;
		Q.pop();

		int maxmove = pos.second+1;
		if(V[maxmove] > V[pos.first]+10) continue;

		while(maxmove < V && V[maxmove] <= V[pos.first]+10) maxmove++;
		if(maxmove == size(V))
		{
			cout << turn+1 << endl;
			return true;
		}

		for(int i=pos.second+1;i<maxmove;i++)
		{
			PII npos = mp(pos.second, i);
			if(visit.count(npos)) continue;
			visit.insert(npos);
			Q.push(mp(npos, turn+1));
		}
	}
	cout << -1 << endl;
	return true;
}

int main(void)
{
	while(process());
}

