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

set<int> avail[1<<4];

void process(int a,int b,int c,int d)
{
	for(int i=0;i<(1<<4);i++)
		avail[i].clear();

	avail[1].insert(a);
	avail[2].insert(b);
	avail[4].insert(c);
	avail[8].insert(d);

	for(int i=0;i<(1<<4);i++)
	{
		for(int j=1;j<i;j++) if((i|j) == i)
		{
			int k = i ^ j;
			foreach(it, avail[j])
			{
				foreach(jt, avail[k])
				{
					avail[i].insert(*it + *jt);
					avail[i].insert(*it - *jt);
					avail[i].insert(*jt - *it);
					avail[i].insert(*it * *jt);
					if( (*jt) && (*it % *jt) == 0)
						avail[i].insert(*it / *jt);
					if( (*it) && (*jt % *it) == 0)
						avail[i].insert(*jt / *it);
				}
			}
		}
	}

	int maxlen = -1, start;
	int len, cur = *(avail[(1<<4)-1].begin()), curs;
	len = 0;
	foreach(it, avail[(1<<4)-1])
	{
		if(*it == cur+1)
		{
			len++;
			cur++;
		}
		else
		{
			if(len >= maxlen)
			{
				maxlen = len;
				start = curs;
			}

			len = 1;
			curs = *it;
			cur = *it;
		}
	}

	if(len >= maxlen)
	{
		maxlen = len;
		start = curs;
	}
	printf("%d to %d\n", start, start+maxlen-1);
}

int main(void)
{
	int a,b,c,d;
	for(int i=1;;i++)
	{
		scanf("%d %d %d %d",&a,&b,&c,&d);
		if(a==0 && b==0 && c==0 && d==0) break;
		printf("Case %d: ",i);
		process(a,b,c,d);
	}
}

