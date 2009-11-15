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

bool process(void)
{
	int n;
	scanf("%d",&n);
	if(n==0) return false;
	vector<rect> V;
	vector<int> VV;
	V.clear();
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
	VV.clear();
	VV.resize(V.size());

	vector<int> prev(V.size());

	int maxv=1;
	for(int i=0;i<V.size();i++)
	{
		VV[i]=1;
		for(int j=0;j<i;j++)
		{
			if(check(V[j],V[i]))
			{
				if(VV[i] < VV[j]+1) 
				{
					VV[i] = VV[j]+1;
					prev[i] = j;
					if(maxv < VV[i]) maxv = VV[i];
				}
			}
		}
	}
	cout << maxv << endl;
	return true;
}

int main(void)
{
	while(process());
}

