#include <iostream>
#include <ctime>
#include <cstdlib>
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
typedef vector<long long> VLL;

template<typename T> int size(const T &a) { return a.size(); }

int makep2(int a)
{
	int ret=1;
	while(ret < a) ret*=2;
	return ret;
}

void mul(VLL a, VLL b, VLL &ret)
{
	if(a.size() < 100)
	{
		ret = VLL(2*size(a));
		for(int i=0;i<size(a);i++)
			for(int j=0;j<size(b);j++)
				ret[i+j] += a[i]*b[j];
		return;
	}

	int sz = size(a);
	VLL ax(a.begin()+sz/2,a.end());
	VLL bx(b.begin()+sz/2,b.end());
	a.resize(sz/2);
	b.resize(sz/2);
	VLL c,cx;
	mul(a,b,c);
	mul(ax,bx,cx);

	for(int i=0;i<size(a);i++)
		a[i] += ax[i];
	for(int i=0;i<size(b);i++)
		b[i] += bx[i];

	VLL mx;
	mul(a,b,mx);
	ret = VLL(sz*2,0);
	for(int i=0;i<c.size();i++)
	{
		mx[i] -= c[i] + cx[i];
		ret[i] += c[i];
		ret[i + sz/2] += mx[i];
		ret[i + sz] += cx[i];
	}
}

int main(void)
{
	VLL a,b;
	VLL cur,next,tmp1,tmp2;

	srand(time(NULL));
	for(int i=0;i<65536;i++)
	{
		a.pb(rand()%2);
		b.pb(rand()%2);
	}

/*
	for(int i=0;i<a.size();i++)
		cout << a[i] << " ";
	cout << endl;
	for(int i=0;i<b.size();i++)
		cout << b[i] << " ";
	cout << endl;
*/	

	VLL c;
	mul(a,b,c);
	for(int i=0;i<size(c);i++)
		cout << c[i] << " ";
	cout << endl;
	return 0;
}
