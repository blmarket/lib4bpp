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
template<typename T> inline bool operator<(const int &a,const vector<T> &b) { return a<b.size(); }

int main(void)
{
	int n = 100;
	cout << n << endl;
	for(int i=0;i<10;i++)
	{
		int a,b,c,d;
		a = rand()%1000;
		b = rand()%1000;
		c = 1+(rand()%1000);
		d = 1+(rand()%1000);
		cout << a << " " << b << " " << a+c << " " << b+d << endl;
	}
	cout << 0 << endl;
}

