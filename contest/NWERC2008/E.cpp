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
typedef long long LL;

template<typename T> int size(const T &a) { return a.size(); }

vector<long long> data;
vector<pair<LL,LL> > mrange;
long long d;

long long near(long long cur, pair<LL,LL> range)
{
	if(cur >= range.first - d && cur <= range.second - d)
}

void process(void)
{
	int n;
	cin >> n >> d;
	data.resize(n);
	for(int i=0;i<n;i++)
	{
		cin >> data[i];
	}
	
	if(abs(data[n-1] - data[0]) > (n-1)*d)
	{
		cout << "impossible" << endl;
		return;
	}

	for(int i=1;i<n-2;i++)
	{
	}
}

int main(void)
{
    int N;
	scanf("%d",&N);
    for(int i=1;i<=N;i++)
    {
        process();
    }
}

