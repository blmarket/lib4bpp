#include <iostream>
#include <algorithm>
#include <cstdio>
#include <cstdlib>
#include <sstream>
#include <queue>
#include <set>
#include <map>
#include <vector>

#define mp make_pair
#define pb push_back
#define sqr(x) ((x)*(x))

using namespace std;

typedef vector<int> VI;
typedef vector<VI> VVI;
typedef vector<string> VS;
typedef pair<int,int> PII;
typedef long long LL;

template<typename T> int size(const T &a) { return a.size(); }
template<typename T> T abs(const T &a) { return (a<0)?-a:a; }

template<typename T1,typename T2,typename T3> T1 & operator<<(T1 &a, const pair<T2,T3> &b)
{
	return a << "<" << b.first << "," << b.second << ">";
}

vector<long long> data;
vector<pair<LL,LL> > mrange;
vector<long long> minval;
long long d;

long long near(long long cur, pair<LL,LL> range)
{
	if(cur < range.first - d) return range.first - d;
	if(cur > range.second + d) return range.second + d;
	return cur;
}

long long getvar(int idx,long long pos)
{
	if(idx == 0) return 0;
	long long maxx = data[0] + d * idx;
	long long minn = data[0] - d * idx;
	if(pos > maxx || pos < minn) return -1;

	pair<LL,LL> range = mrange[idx-1];
	if(pos < range.first - d) return getvar(idx-1, pos + d) + abs(data[idx] - pos);
	if(pos > range.second + d) return getvar(idx-1, pos - d) + abs(data[idx] - pos);
	return minval[idx-1] + abs(data[idx] - pos);
}

LL bsearch(LL s,LL e,int idx,LL tgt)
{
	while(abs(e-s) > 3)
	{
		LL m = (s+e)/2;
		if(getvar(idx,m) == tgt)
			s=m;
		else
			e=m;
	}

	while(s!=e)
	{
		LL m;
		if(s<e) m= s+1; else m =s-1;
		if(getvar(idx,m) != tgt) return s;
		s=m;
	}

	return s;
}

void process(void)
{
	int n;
	cin >> n >> d;
	data.resize(n);
	for(int i=0;i<n;i++)
	{
		cin >> data[i];
	}
	
	if(abs(data[n-1] - data[0]) > (n-1)*d)
	{
		cout << "impossible" << endl;
		return;
	}

	mrange.resize(n);
	minval.resize(n);
	mrange[0] = mp(data[0],data[0]);
	minval[0] = 0;

	for(int i=1;i<n-1;i++)
	{
		long long minpos = near(data[i], mrange[i-1]);
		minval[i] = getvar(i, minpos);
		mrange[i] = mp(minpos,minpos);
		long long tmp = getvar(i,minpos+1);
		if(tmp != -1 && tmp == minval[i])
		{
			long long s = minpos+1, e = data[0] + i * d;
			mrange[i] = mp(minpos,bsearch(s,e,i,minval[i]));
			continue;
		}
		tmp = getvar(i, minpos-1);
		if(tmp != -1 && tmp == minval[i])
		{
			long long s = minpos-1, e= data[0] - i*d;
			mrange[i] = mp(bsearch(s,e,i,minval[i]),minpos);
			continue;
		}
	}
	cout << getvar(n-1,data[n-1]) << endl;
}

int main(void)
{
    int N;
	scanf("%d",&N);
    for(int i=1;i<=N;i++)
    {
        process();
    }
}

