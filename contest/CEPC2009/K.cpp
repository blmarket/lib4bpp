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

int n,L;
VI cur,next;
VI indata;

template<typename T>
void alloc(const T &s1, const T &e1, const T &s2, const T &e2)
{
	VI stack;
	stack.clear();
	int curpos = 0;
	T jter = s1;

	for(T iter = s2; iter != e2; ++iter)
	{
		if( (*iter) == 0 )
		{
			stack.pb(0);
			(*jter) = 0;
			++jter;
		}
		else
		{
			int tmp = *iter;
			if(stack.size())
			{
				stack.back() += 1;
				int len = min(size(stack), tmp);
				int accum = 0;
				for(int i=0;i<len;i++)
				{
					accum += *(stack.rbegin() + i);
					int &value = *(jter + tmp - 1 - i);
					if(value == -1 || value > accum)
						value = accum;
				}
			}
			jter += tmp;
		}
	}
}

void process(void)
{
	scanf("%d %d",&n,&L);
	cur = VI(L,0);
	for(int i=0;i<n;i++)
	{
		next = VI(L,-1);
		int m;
		scanf("%d",&m);
		indata.resize(m);
		for(int j=0;j<m;j++)
			scanf("%d",&indata[j]);
		alloc( next.begin(), next.end(),indata.begin(), indata.end());
		alloc( next.rbegin(), next.rend(), indata.rbegin(), indata.rend());

		for(int j=0;j<L;j++)
		{
			if(cur[j] == -1 || next[j] == -1)
				cur[j] = -1;
			else
				cur[j] += next[j];
		}
	}

	int minval = -1;
	for(int i=0;i<size(cur);i++) if(cur[i] != -1)
	{
		if(minval == -1 || minval > cur[i]) minval = cur[i];
	}
	printf("%d\n",minval);
	for(int i=0;i<size(cur);i++)
	{
		if(minval == cur[i])
			printf("%d ",i);
	}
	printf("\n");
}

int main(void)
{
	int T;
	scanf("%d",&T);
	for(int i=0;i<T;i++)
		process();
	return 0;
}

