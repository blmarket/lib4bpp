#include <iostream>
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

vector<PII> v1,v2;
vector<vector<int> > edge;
vector<int> used;
vector<bool> visit;

bool try_flow(int a)
{
	if(visit[a]) return false;
	visit[a]=true;
	for(int i=0;i<edge[a].size();i++)
	{
		int n2 = edge[a][i];
		if(used[n2] == -1 || try_flow(used[n2]))
		{
			used[n2] = a;
			return true;
		}
	}
	return false;
}

void process(void)
{
	int a,b,n;
	scanf("%d %d %d",&a,&b,&n);
	edge.clear();
	v1.clear();
	v2.clear();
	for(int i=0;i<n;i++)
	{
		char a,c;
		int b,d;
		scanf(" %c%d %c%d",&a,&b,&c,&d);
		if(a=='C')
		{
			v1.pb(mp(b,d));
		}
		else
		{
			v2.pb(mp(d,b));
		}
	}
	edge.resize(v1.size());
	for(int i=0;i<v1.size();i++)
	{
		for(int j=0;j<v2.size();j++)
		{
			if(v1[i].first == v2[j].first || v1[i].second == v2[j].second)
			{
				edge[i].pb(j);
			}
		}
	}

	used = vector<int>(v2.size(),-1);
	int cnt=0;
	for(int i=0;i<v1.size();i++)
	{
		visit = vector<bool>(v1.size(),false);
		if(try_flow(i))
		{
			cnt++;
		}
	}
	printf("%d\n",n-cnt);
}

int main(void)
{
    int N;
	scanf("%d",&N);
	for(int i=0;i<N;i++) process();
}

