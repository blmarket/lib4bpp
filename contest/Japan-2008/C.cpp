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

template<typename T> inline int size(const T &a) { return a.size(); }

struct state
{
	state() {};
	state(int h,int m,int s) : h(h),m(m),s(s) {};
	int h,m,s;

	bool operator<(const state &a) const
	{
		if(h != a.h) return h<a.h;
		if(m != a.m) return m<a.m;
		return s < a.s;
	}

	bool operator==(const state &a) const
	{
		return h==a.h && m==a.m && s==a.s;
	}

	state operator-(const state &a) const
	{
		int et = (h-a.h)*3600 + (m - a.m) * 60 + (s-a.s);
		if(et < 0) et += 3600*12;
		state ret;
		ret.h = et/3600;
		et%=3600;
		ret.m = et/60;
		et%=60;
		ret.s = et;
		return ret;
	}
};

template<typename T>
T & operator<<(T &a, const state &b)
{
	printf("%02d:%02d:%02d",(b.h)%12,b.m,b.s);
	return a;
}

template<typename T>
inline bool operator<(const int &a, const vector<T> &b) { return a < size(b); }

bool check2(int h,int m,int s)
{
	int hp = h % 5;
	if(m/12 != hp) return false;
	return true;
}

vector<state> check(int a,int b,int c)
{
	vector<state> ret;
	if(check2(a,b,c)) ret.pb(state(a/5,b,c));
	if(check2(a,c,b)) ret.pb(state(a/5,c,b));
	if(check2(b,a,c)) ret.pb(state(b/5,a,c));
	if(check2(b,c,a)) ret.pb(state(b/5,c,a));
	if(check2(c,a,b)) ret.pb(state(c/5,a,b));
	if(check2(c,b,a)) ret.pb(state(c/5,b,a));
	return ret;
}

vector<state> assume(int a,int b,int c)
{
	vector<state> ret;
	for(int i=0;i<60;i++)
	{
		vector<state> tmp = check(a,b,c);
		for(int j=0;j<tmp;j++)
			ret.pb(tmp[j]);
		a++;b++;c++;
		a%=60;
		b%=60;
		c%=60;
	}
	sort(ret.begin(),ret.end());
	ret.erase(unique(ret.begin(),ret.end()),ret.end());
	return ret;
}

bool process(void)
{
	int n;
	scanf("%d",&n);
	if(n==0) return false;

	vector<pair<state,int> > total;
	total.clear();

	for(int i=0;i<n;i++)
	{
		int a,b,c;
		scanf("%d %d %d",&a,&b,&c);
		vector<state> pos = assume(a,b,c);
		for(int j=0;j<pos;j++)
			total.pb(mp(pos[j],i));
	}
	sort(total.begin(),total.end());

	int sz = size(total);
	for(int i=0;i<sz;i++)
	{
		total.pb(total[i]);
		total.back().first.h += 12;
	}

	vector<int> a0(n);
	int n1=0;
	int tail=0;
	state minlen(24,0,0);
	state t1,t2;
	for(int i=0;i<total;i++)
	{
		int tmp = total[i].second;
		++a0[tmp];
		if(a0[tmp] == 1) n1++;
		if(n1 == size(a0))
		{
			while(a0[total[tail].second] > 1)
			{
				a0[total[tail].second]--;
				tail++;
			}
			state len = total[i].first - total[tail].first;
			if(len < minlen) { minlen = len; t1 = total[tail].first; t2 = total[i].first; }
		}
	}

	cout << t1 << " " << t2 << endl;

	return true;
}

int main(void)
{
	while(process());
}

