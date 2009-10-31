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

const int stick[] = {6,2,5,5,4,5,6,3,7,6};

vector<int> minlen;

void process(void)
{
	int n;
	scanf("%d",&n);
	int nn = n;

	bool first=true;

	string str;
	while(n)
	{
		for(int i=first;i<10;i++)
		{
			int next = n - stick[i];
			if(next < 0) continue;
			if(minlen[next] == minlen[n]-1)
			{
				n=next;
				str += '0'+i;
				break;
			}
		}
		first=false;
	}
	cout << str << " ";

	if(nn % 2)
	{
		cout << "7";
		nn-=3;
	}
	while(nn)
	{
		cout << "1";
		nn-=2;
	}
	cout << endl;
}

void precalc()
{
	minlen.pb(0);
	minlen.pb(-1);
	for(int i=2;i<=100;i++)
	{
		minlen.pb(-1);
		for(int j=0;j<10;j++)
		{
			if(stick[j] > i) continue;
			if(minlen[i-stick[j]] == -1) continue;
			int len = minlen[i-stick[j]] + 1;
			if(minlen[i] == -1 || minlen[i] > len) minlen[i] = len;
		}
	}
}

int main(void)
{
	precalc();
    int N;
	scanf("%d",&N);
	for(int i=0;i<N;i++)
		process();
}

