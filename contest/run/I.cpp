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

VI data;
VI dyna;

void process(void)
{
	int n,m;
	multiset<int> S;
	scanf("%d %d",&n,&m);
	data.resize(n);
	dyna.resize(n,-1);
	for(int i=0;i<n;i++)
	{
		scanf("%d",&data[i]);
	}
	for(int i=0;i<m;i++)
	{
		dyna[i] = data[i];
		S.insert(dyna[i]);
	}
	for(int i=m;i<n;i++)
	{
		dyna[i] = *S.begin() + data[i];
		S.erase(S.find(dyna[i-m]));
		S.insert(dyna[i]);
	}

	int mind = -1;
	for(int i=n-m;i<n;i++)
	{
		if(mind < 0 || mind > dyna[i]) mind = dyna[i];
	}
	cout << mind << endl;
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

