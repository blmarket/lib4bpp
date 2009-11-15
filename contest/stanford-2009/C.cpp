#include <iostream>
#include <algorithm>
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
template<typename T> inline bool operator<(const int &a,const vector<T> &b) { return a<b.size(); }

int a[20];

bool process(void)
{
	int n;
	scanf("%d",&n);
	if(n==0) return false;

	bool flag=false;
	for(int i=0;i<20;i++)
	{
		scanf("%d",&a[i]);
		if(a[i] != 20-i) flag=true;
	}

	if(n == 21)
	{
		cout << "Carl can't win" << endl;
		return true;
	}

	if(((n % 21)!=0) || flag)
	{
		cout << "Carl can win" << endl;
		return true;
	}

	cout << "Carl can't win" << endl;
	return true;
}

int main(void)
{
	while(process());
}

