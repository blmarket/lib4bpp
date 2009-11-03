#include <iostream>
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

void multiply(VLL V1, VLL V2, VLL &V3)
{
	int siz = max(V1.size(),V2.size()); siz = makep2(siz);
	V1.resize(siz,0);
	V2.resize(siz,0);
	if(siz == 1)
	{
		V3.resize(1);
		V3[0] = V1[0] * V2[0];
		return;
	}
	VLL V5(V1.begin()+siz/2,V1.end());
	VLL V6(V2.begin()+siz/2,V2.end());
	VLL V7;
	multiply(V5,V6,V7);
	V1.resize(siz/2);
	V2.resize(siz/2);
	VLL V8;
	multiply(V1,V2,V8);
	for(int i=0;i<siz/2;i++)
	{
		V1[i] += V5[i];
		V2[i] += V6[i];
	}
	VLL V9;
	multiply(V1,V2,V9);
	for(int i=0;i<V9.size();i++)
	{
		V9[i] -= V7[i] + V8[i];
	}

	V8.resize(siz*2-1,0);
	for(int i=0;i<V9.size();i++)
	{
		V8[i+siz/2] += V9[i];
		V8[i+siz] += V7[i];
	}
	V3=V8;
}

int main(void)
{
	VLL a,b;
	for(int i=0;i<3000;i++)
	{
		a.pb(rand()%10);
		b.pb(rand()%10);
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
	multiply(a,b,c);
/*	for(int i=0;i<c.size();i++)
	{
		cout << c[i] << " ";
	}
	cout << endl;*/
}
