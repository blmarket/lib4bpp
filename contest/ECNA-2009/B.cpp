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

int N;
vector<int> as,bs;
vector<double> known,elasp;

string mask(int a)
{
	if(a==0) return "0";
	return mask(a/2) + string(1,'0'+a%2);
}

double getprob(int n,int a,int b,bool flag)
{
	int aa = as[n];
	int bb = bs[n];
	double tot = (aa-a)*known[n] + (bb-b)*elasp[n];
	if(flag) return known[n]/tot; else return elasp[n]/tot;
}

struct state
{
	int correct;
	vector<int> usea,useb;

	bool operator<(const state &a) const
	{
		if(correct != a.correct) return correct<a.correct;
		if(usea != a.usea) return usea < a.usea;
		return useb < a.useb;
	}
};

map<state,double> memo;
int p3[] = {1,3,9,27,81,243};

double go(const state &a)
{
	if(a.correct == (1<<N)-1) return 1;

	if(memo.count(a)) return memo[a];

	double maxr = 0;
	for(int i=0;i<(1<<N);i++)
	{
		double prob[5] = {0};
		if(i & (a.correct)) continue;
		state tmp = a;

		bool illegal=false;
		for(int j=0;j<N;j++)
		{
			if(a.correct & (1<<j))
			{
				prob[j] = 0;
				continue;
			}
			if((i & (1<<j)) != 0)
			{
				if(a.usea[j] == as[j]) { illegal=true; break; }
				tmp.usea[j]++;
				prob[j] = getprob(j,a.usea[j],a.useb[j],true);
			}
			else
			{
				if(a.useb[j] == bs[j]) { illegal=true; break; }
				tmp.useb[j]++;
				prob[j] = getprob(j,a.usea[j],a.useb[j],false);
			}
		}
		if(illegal) continue;

		double ret = 0;
		for(int j=0;j<(1<<N);j++)
		{
			if(j & a.correct) continue;
			if((a.correct | j) == (a.correct)) continue;
			double pp = 1;
			for(int k=0;k<N;k++)
			{
				if(j & (1<<k))
					pp *= prob[k];
				else
					pp *= (1. - prob[k]);
				if(pp < 1e-6) break;
			}
			if(pp < 1e-6) continue;

			tmp.correct = a.correct | j;
			ret += pp * go(tmp);
		}
		if(maxr < ret) maxr = ret;
	}

	return memo[a]=maxr;
}

bool process(int tcase)
{
	cin >> N;
	if(N==0) return false;
	as.resize(N);
	bs.resize(N);
	known.resize(N);
	elasp.resize(N);
	memo.clear();
	for(int i=0;i<N;i++)
	{
		cin >> as[i] >> bs[i] >> known[i];
		swap(as[i],bs[i]);
		bs[i] -= as[i];

		double tot = known[i];
		if(known[i] > 1e-6) known[i] /= as[i];
		if(known[i] > 1+1e-6)
		{
			cerr << "data wrong" << endl;
			return false;
		}
		elasp[i] = (1.0-tot)/(bs[i]?bs[i]:1);
	}

	state tmp;
	tmp.correct=0;
	tmp.usea = VI(N,0);
	tmp.useb = VI(N,0);

	double ret = go(tmp);
	ret *= 1000;
	ret += 0.5;
	ret = (int)ret;
	ret /= 1000;
	cout << ret << endl;
	return true;
}

int main(void)
{
	for(int i=1;;i++)
    {
        if(!process(i)) break;
    }
	return 0;
}

