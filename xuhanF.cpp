#include <iostream>
#include <numeric>
#include <string>
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

using namespace std;

typedef vector<int> VI;
typedef vector<VI> VVI;
typedef vector<string> VS;
typedef pair<int,int> PII;
typedef complex<double> Point;

template<typename T> inline int size(const T &a) { return a.size(); }
template<typename T> inline bool operator<(const int &a,const vector<T> &b) { return a<b.size(); }

const char *names = "YHLM";
int SY_jing, XX_su, SY_su, yurun_jing, yurun_shen, shuerguo_shen;

struct status
{
	int maxjing, maxshen, su, d1x, d2x, d1s, d2s, wad, ssd, ssq, ssp, q1, q2, jing, qi, shen;

	void read()
	{
		scanf("%d %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d", &maxjing, &maxshen, &su, &d1x, &d2x, &d1s, &d2s, &wad, &ssd, &ssq, &ssp, &q1, &q2, &jing, &qi, &shen);
	}
};

struct curstat
{
	curstat(const status &in) 
		: base(in)
		, dealt(0) 
		, dead(false)
		, spused(false)
	{ jing = in.jing, qi = in.qi, shen = in.shen; }

	void damaged(int dmg)
	{
		jing -= dmg;
		if(jing <= 0)
			dead = true;
	}

	void attack1()
	{
		dealt += base.wad;
		damaged(base.wad);
		qi += base.q1;
		if(qi > 100) qi = 100;
	}

	void attack2()
	{
		qi += base.q1;
		if(qi > 100) qi = 100;
	}

	void hpup()
	{
		jing += yurun_jing;
		shen -= yurun_shen;
		if(shen < 0) dead = true;
		if(jing > base.maxjing) jing = base.maxjing;
	}

	void spup()
	{
		shen += shuerguo_shen;
		if(shen > base.maxshen) shen = base.maxshen;
	}

	void special()
	{
		dealt += base.ssd;
		qi -= base.ssq;
		if(qi < 0)
			dead = true;
		if(spused)
			dead = true;
		spused = true;
		if(base.ssp)
			damaged(base.ssd);
	}

	status base;
	int jing, qi, shen;
	int dealt;
	bool dead;
	bool spused;

	bool operator<(const curstat &a) const
	{
		if(jing != a.jing) return jing<a.jing;
		if(qi != a.qi) return qi<a.qi;
		if(shen != a.shen) return shen<a.shen;
		return spused < a.spused;
	}
};

template<typename T> T& operator<<(T &a, const curstat &b)
{
	return a << "(" << b.jing << "," << b.qi << "," << b.shen << "," << b.spused << ":" << b.dealt << ")";
}

status basedata[4];
status curdata[3];

void addif(map<curstat, int> &M, const curstat &in)
{
	if(in.dead) return;
	int &tmp = M[in];
	if(tmp < in.dealt) tmp = in.dealt;
}

void chkdeal(const status &base, int *deal, int pos)
{
	vector<curstat> V;
	V.pb(curstat(base));
	int su = base.su;
	for(int i=1;i<=12;i++)
	{
		typedef map<curstat,int> MType;
		MType M;
		M.clear();
		if((i % su) == 0) // my turn!
		{
			for(int j=0;j<V.size();j++)
			{
				curstat tmp = V[j];
				tmp.attack1();
				addif(M,tmp);
				tmp = V[j];
				tmp.attack2();
				addif(M,tmp);
				tmp = V[j];
				tmp.hpup();
				addif(M,tmp);
				tmp = V[j];
				tmp.spup();
				addif(M,tmp);
				tmp = V[j];
				tmp.special();
				addif(M,tmp);
			}
		}
		else
		{
			for(int j=0;j<V.size();j++)
				M[V[j]] = V[j].dealt;
		}

		int damaged = 0;
		int addqi = 0;
		if((i % XX_su) == 0)
		{
			int tmp = (i / XX_su);
			if((tmp % 4) == 0)
				damaged += base.d2x;
			else
			{
				if((tmp%4) == pos)
				{
					damaged += base.d1x;
					addqi += base.q2;
				}
			}
		}
		if((i % SY_su) == 0)
		{
			int tmp = (i / SY_su);
			if((tmp % 4) == 0)
				damaged += base.d2s;
			else
			{
				if((tmp % 4) == pos)
				{
					damaged += base.d1s;
					addqi += base.q2;
				}
			}
		}

		V.clear();

		if(M.size() == 0)
		{
			deal[i] = -1;
			break;
		}

		for(MType::iterator it=M.begin(); it != M.end(); ++it)
		{
			deal[i] = max(deal[i], it->second);
			if(it->first.jing <= damaged) continue;
			curstat tmp = it->first;
			tmp.jing -= damaged;
			tmp.qi += addqi;
			tmp.dealt = it->second;
			if(tmp.qi > 100) tmp.qi = 100;

			V.pb(tmp);
		}
/*
		for(int j=0;j<size(V);j++)
			cout << V[j] << " ";
		cout << endl;
*/
	}
}

int calc(void)
{
	int dealmap[3][15] = {0};
	for(int i=0;i<3;i++)
	{
		chkdeal(curdata[i],dealmap[i],i+1);
/*		for(int j=0;j<15;j++)
			cout << dealmap[i][j] << " ";
		cout << endl;*/
	}

	int sum=0;
	for(int i=1;i<15;i++)
	{
		for(int j=0;j<3;j++)
		{
			if(dealmap[j][i] == -1) return -1;
			sum += dealmap[j][i] - dealmap[j][i-1];
			if(sum >= SY_jing) return i;
		}
	}
	return -1;
}

bool process(int tcase)
{
	scanf("%d %d %d %d %d %d", &SY_jing, &XX_su, &SY_su, &yurun_jing, &yurun_shen, &shuerguo_shen);
	if(SY_jing == 0 && XX_su == 0 && SY_su == 0 && yurun_jing == 0 && yurun_shen == 0 && shuerguo_shen == 0) return false;
	XX_su = 5 - XX_su;
	SY_su = 5 - SY_su;
	for(int i=0;i<4;i++)
	{
		basedata[i].read();
		basedata[i].su = 5 - basedata[i].su;
	}

	int minturn = -1;
	vector<string> ret;

	string curstr(3,' ');
	for(int i=0;i<4;i++)
	{
		curdata[0] = basedata[i];
		curstr[0] = names[i];
		for(int j=0;j<3;j++)
		{
			int rj = j;
			if(j >= i) rj = j+1;
			curdata[1] = basedata[rj];
			curstr[1] = names[rj];
			for(int k=0;k<2;k++)
			{
				int rk = k;
				if(rk >= i)
				{
					rk++;
					if(rk >= rj)
						rk++;
				}
				else
				{
					if(rk >= rj)
					{
						rk++;
						if(rk >= i)
							rk++;
					}
				}
				curdata[2] = basedata[rk];
				curstr[2] = names[rk];
//				cout << names[i] << names[rj] << names[rk] << ":";
				int turns = calc();
				if(turns > 12) turns = -1;
				if(turns < 0) continue;
				if(minturn < 0 || minturn > turns)
				{
					minturn=turns;
					ret.clear();
				}
				if(minturn == turns)
				{
					ret.pb(curstr);
				}
			}
		}
	}

	sort(ret.begin(), ret.end());
	cout << "Case " << tcase << ": " << minturn;
	for(int i=0;i<size(ret);i++)
		cout << " " << ret[i];
	cout << endl << endl;

	return true;
}

int main(void)
{
	for(int i=1;process(i);++i);
	return 0;
}

