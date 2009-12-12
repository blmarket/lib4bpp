#include <iostream>
#include <string>
#include <sstream>
#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <queue>
#include <set>
#include <map>
#include <memory>
#include <vector>
#include <algorithm>

#define mp make_pair
#define pb push_back
#define sqr(x) ((x)*(x))
#define foreach(it,c) for(typeof((c).begin()) it = (c).begin(); it != (c).end(); ++it)

using namespace std;

typedef vector<int> VI;
typedef vector<VI> VVI;
typedef vector<string> VS;
typedef vector<long long> VLL;
typedef vector<VLL> VVLL;
typedef pair<int,int> PII;
typedef long long LL;

template<typename T> int size(const T &a) { return a.size(); }

map<string,int> strMap;
vector<string> rev;
int getval(const string &str)
{
	map<string,int>::iterator iter = strMap.find(str);
	if(iter == strMap.end()) 
	{
		strMap[str] = rev.size();
		rev.push_back(str);
		return rev.size()-1;
	}
	return iter->second;
}

struct rule
{
	rule(int a,int b,int c,int d):a(a),b(b),c(c),d(d) {}
	int a,b,c,d;
};

vector<rule> Vrule;
map<int, vector<rule> > ruleMap;
vector<vector<map<int, long long> > > dyna;
struct outp
{
	outp(int s,int e,const string &str) : s(s),e(e),str(str) {};

	int s;
	int e;
	string str;

	bool operator==(const outp &a) const
	{
		return s==a.s && e==a.e && str==a.str;
	}

	bool operator<(const outp &a) const
	{
		if(s != a.s) return s<a.s;
		if(e != a.e) return e<a.e;
		return str < a.str;
	};
};

long long maxL;
vector<outp> maxlifes;

void mixup(const map<int, long long> &tmp1, const map<int, long long> &tmp2, map<int, long long> &tgt,int jj,int ii)
{
	map<int,LL>::const_iterator iter1,iter2;

	for(iter1 = tmp1.begin(); iter1 != tmp1.end(); ++iter1)
	{
		const vector<rule> &rr = ruleMap[iter1->first];
		for(int i=0;i<rr.size();i++)
		{
			iter2 = tmp2.find(rr[i].b);
			if(iter2 == tmp2.end()) continue;
			long long tmp = (iter1->second + iter2->second) * rr[i].d;

//			cout << jj << " " << jj+ii << " born " << rev[rr[i].c] << endl;

			if(tmp > maxL)
			{
				maxL = tmp;
				maxlifes.clear();
			}

			if(tmp == maxL)
			{
				maxlifes.push_back(outp(jj,jj+ii,rev[rr[i].c]));
			}

			long long &tmp2 = tgt[rr[i].c];
			if(tmp2 < tmp) tmp2 = tmp;
		}
	}
}

int main(void)
{
	char buffer[1024768];
	while(true)
	{
		fgets(buffer,1024768,stdin);
		istringstream sin(buffer);

		if(strlen(buffer) < 5) break;
		
		string a,b,c;
		int d;
		if((sin >> a >> b >> c >> d))
		{
			Vrule.pb(rule(getval(b),getval(c),getval(a),d));
			Vrule.pb(rule(getval(c),getval(b),getval(a),d));
		}
		else
			break;
	}

	for(int i=0;i<Vrule.size();i++)
	{
		ruleMap[Vrule[i].a].push_back(Vrule[i]);
	}

	while(true)
	{
		if(fgets(buffer, 1024768, stdin) == NULL) break;
		istringstream sin(buffer);

		vector<int> ntoken;
		string token;

		maxL = 1;
		maxlifes.clear();

		for(int i=0;sin>>token;i++)
		{
			if(token == "") break;
			if(strMap.find(token) == strMap.end()) ntoken.pb(strMap.size());
			else ntoken.pb(strMap[token]);
			token = "";
		}
		if(ntoken.size() == 0) break;
		int n = ntoken.size();
		dyna.clear();
		dyna.resize(n);
		for(int i=0;i<n;i++)
			dyna[i].resize(n);

		for(int i=0;i<n;i++)
			dyna[i][i][ntoken[i]] = 1;

		for(int i=1;i<n;i++)
		{
			for(int j=0;j+i<n;j++)
			{
				map<int, LL> &tgt = dyna[j][j+i];
				for(int k=j;k<j+i;k++)
				{
					// j~k, k+1~j+i
					map<int, LL> &tmp1 = dyna[j][k], &tmp2 = dyna[k+1][j+i];
					mixup(tmp1,tmp2,tgt,j,i);
					mixup(tmp2,tmp1,tgt,j,i);
				}
			}
		}

		sort(maxlifes.begin(), maxlifes.end());
		maxlifes.erase(unique(maxlifes.begin(), maxlifes.end()), maxlifes.end());

		if(maxlifes.size() == 0)
		{
			cout << "0 0" << endl;			
		}
		else
		{
			cout << maxlifes.size() << " " << maxL << endl;
			for(int i=0;i<maxlifes.size();i++)
			{
				cout << maxlifes[i].str << " " << maxlifes[i].s+1 << " " << maxlifes[i].e+1 << endl;
			}
		}
	}
}
