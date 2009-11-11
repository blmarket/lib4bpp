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

int n,m;
VVI data;
VI factor1,factor2;

void factorize(int a,VI &ret)
{
	ret.clear();
	for(int i=1;i<=a;i++)
		if((a % i) == 0) ret.pb(i);
}

int getf(int a)
{
	int ret=0;
	for(int i=1;i<=a;i++)
	{
		if((a%i)==0) ret++;
	}
	return ret;
}

void gcdit(VVI &a)
{
	int gcd = a[0][0];
	for(int i=0;i<size(a);i++)
		for(int j=0;j<size(a[i]);j++)
			gcd = __gcd(gcd,a[i][j]);
	for(int i=0;i<size(a);i++)
		for(int j=0;j<size(a[i]);j++)
			a[i][j] /= gcd;
}

bool process(int tcase)
{
	scanf("%d %d",&n,&m);
	if(n == 0 && m == 0) return false;
	data = VVI(n,VI(m));
	for(int i=0;i<n;i++)
	{
		for(int j=0;j<m;j++)
		{
			scanf("%d",&data[i][j]);
		}
	}
	factorize(n,factor1);
	factorize(m,factor2);

	int ret=0;

	for(int i=0;i<size(factor1);i++)
	{
		int f1 = factor1[i];
		int rf1 = n/f1;
		for(int j=0;j<size(factor2);j++)
		{
			int f2 = factor2[j];
			int rf2 = m/f2;

			if(f1==1 && f2==1) continue;
			if(rf1==1 && rf2==1) continue;

			VVI checker = VVI(f1,VI(f2));
			for(int k=0;k<f1;k++)
			{
				for(int l=0;l<f2;l++)
				{
					checker[k][l] = data[k*rf1][l*rf2];
				}
			}
			gcdit(checker);

			int gmx = -1;

			bool checked=true;
			for(int k=0;k<rf1;k++)
			{
				for(int l=0;l<rf2;l++)
				{
					int mulx = data[k][l] / checker[0][0];
					if(gmx == -1) gmx = mulx; else gmx = __gcd(gmx, mulx);
					for(int a=0;a<f1;a++)
					{
						for(int b=0;b<f2;b++)
						{
							const int &dat = data[k+a*rf1][l+b*rf2];
							
							if((mulx != data[k+a*rf1][l+b*rf2] / checker[a][b]) || (dat % checker[a][b]))
							{
								checked=false;
								break;
							}
						}
						if(!checked) break;
					}
					if(!checked) break;
				}
				if(!checked) break;
			}

			if(checked)
			{
				ret+=getf(gmx);
			}
		}
	}

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

