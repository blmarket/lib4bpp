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

template<typename T> int size(const T &a) { return a.size(); }

int n,k;

void go(int a,int b)
{
	while(true)
	{
		if(b == 0) b = a;
		
		if(a==n)
		{
			cout << b << " ";
			return;
		}
		int nn = a+1;
		int pos = k % nn;

		a=nn; b=(b+pos)%nn;
	}
}

void process(void)
{
	n=300000;
	k=454321;

	go(3,k%3);
	go(2,k%2);
	go(1,0);
	cout << endl;
}

int main(void)
{
	process();
}

