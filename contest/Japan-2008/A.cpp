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
	int n,w;
	vector<int> V;
	scanf("%d %d",&n,&w);
	if(n==0 && w==0) return false;
	V.clear();
	V.resize(1);
	for(int i=0;i<n;i++)
	{
		int tmp;
		scanf("%d",&tmp);
		tmp /= w;
		if(V.size() <= tmp) V.resize(tmp+1);
		V[tmp]++;
	}

	int maxv = V[0];
	for(int i=0;i<size(V);i++)
		if(V[i] > maxv) maxv = V[i];

	double ret = 0.01;

	for(int i=0;i<size(V);i++)
	{
		ret += (double)V[i] / maxv * (size(V)-1-i) / (size(V)-1);
	}

	printf("%.12lf\n",ret);
	return true;
}

int main(void)
{
	while(process());
}

