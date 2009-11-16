#include <iostream>
#include <algorithm>
#include <string>
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
#define TYPE(it) typeof(it)
#define foreach(it,c) for(typeof((c).begin()) it = (c).begin(); it != (c).end(); ++it)

using namespace std;

typedef vector<int> VI;
typedef vector<VI> VVI;
typedef vector<string> VS;
typedef pair<int,int> PII;
typedef long long LL;

struct rect
{
	int x0,y0,x1,y1;
};

bool comp(const rect &a, const rect &b)
{
	return a.x0 < b.x0;
}

bool check(const rect &a,const rect &b)
{
	return (a.x1 < b.x0 && a.y1 < b.y0);
}

map<int, PII> memo;

PII get_max(int y)
{
	map<int,PII>::iterator iter = memo.lower_bound(y);
	if(iter == memo.begin()) return mp(0,-1);
	--iter;
	return iter->second;
}

void add_point(int y,int v,int chk)
{
	if(get_max(y).first >= v) return;
	memo[y] = mp(v,chk);

	TYPE(memo.begin()) iter = memo.find(y);
	for(++iter;iter != memo.end();)
	{
		if(iter->second.first <= v)
		{
			TYPE(iter) jter = iter;
			++iter;
			memo.erase(jter);
		}
		else
		{
			++iter;
		}
	}
}

bool process(void)
{
	int n;
	scanf("%d",&n);
	if(n==0) return false;
	vector<rect> V;
	vector<int> VV;
	V.clear();
	memo.clear();
	for(int i=0;i<n;i++)
	{
		int a,b,c,d;
		scanf("%d %d %d %d",&a,&b,&c,&d);
		rect tmp;
		tmp.x0 = a;
		tmp.y0 = b;
		tmp.x1 = c;
		tmp.y1 = d;
		V.pb(tmp);
	}
	sort(V.begin(),V.end(),comp);

	set<pair<PII,PII> > nids;

	int ret = 0;
	for(int i=0;i<V.size();i++)
	{
		while(nids.size())
		{
			pair<PII,PII> tmp = *(nids.begin());
			if(tmp.first.first < V[i].x0)
			{
				add_point(tmp.first.second, tmp.second.first, tmp.second.second);
				nids.erase(nids.begin());
			}
			else
			{
				break;
			}
		}

		int tmp1 = get_max(V[i].y0).first + 1;
		int tmp2 = get_max(V[i].y0).second;
		if(ret < tmp1) ret = tmp1;
//		cout << i << " " << tmp1 << " " << tmp2 << endl;
		nids.insert(mp(mp(V[i].x1, V[i].y1),mp(tmp1,i)));
	}

	cout << ret << endl;
	return true;
}

int main(void)
{
	while(process());
}
