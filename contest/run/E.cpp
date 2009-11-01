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
VI data;

long long solve1(void)
{
	map<int,long long> M;
	int sum = 0;
	M[0]=1;
	for(int i=0;i<data.size();i++)
	{
		sum = (sum + data[i]) % k;
		M[sum]++;
	}

	long long ret=0;
	foreach(it,M)
	{
		ret += (it->second-1) * it->second / 2;
		ret %= 20091101;
	}
	return ret;
}

int solve2(void)
{
	int ret=0;
	int sum=0;
	set<int> S;
	S.insert(0);
	for(int i=0;i<data.size();i++)
	{
		sum = (sum + data[i]) % k;
		if(S.count(sum))
		{
			sum=0;
			ret++;
			S.clear();
		}
		S.insert(sum);
	}

	return ret;
}

void process(void)
{
	scanf("%d %d",&n,&k);
	data.resize(n);
	for(int i=0;i<n;i++)
	{
		scanf("%d",&data[i]);
	}
	cout << solve1() << " " << solve2() << endl;
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

