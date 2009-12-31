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

int n,m,d;
vector<int> data;

bool check(LL a)
{
	int cnt = 0;
	int pos = 0;

	while(pos < n)
	{
		int mxsz = 1;
		LL sum1=data[pos],sum2=data[pos+1];
		for(int sz=1;sz<=d && pos+sz*2 < data.size();sz++)
		{
			if(sum1 <= a && sum2 <= a) mxsz = sz;
			sum1 += data[pos+sz];
			sum2 += -data[pos+sz]+data[pos+sz*2]+data[pos+sz*2+1];
		}
		pos += mxsz*2;
		cnt++;
	}

	return cnt <= m;
}

void process(void)
{
	scanf("%d %d %d",&n,&m,&d);
	LL s = -1;
	data.resize(n);
	for(int i=0;i<n;i++)
	{
		scanf("%d",&data[i]);
		if(s<data[i]) s=data[i];
	}

	m--;

	if((n%2)==1 || n < m*2)
	{
		printf("BAD\n");
		return;
	}

	LL e=1e9;
	while(s<e)
	{
		LL m = (s+e)/2;
		if(check(m))
		{
			e=m;
		}
		else
		{
			s=m+1;
		}
	}

	cout << e << endl;
}

int main(void)
{
	int T;
	scanf("%d",&T);
	for(int i=0;i<T;i++)
		process();
	return 0;
}

