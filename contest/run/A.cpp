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

void process(void)
{
	int n;
	vector<int> data;
	scanf("%d",&n);
	data.resize(n);
	for(int i=0;i<n;i++)
		scanf("%d",&data[i]);
	sort(data.begin(),data.end());

	int maxsum = 0;
	for(int i=0;i<(n/2);i++)
	{
		int sum = data[i] + data[n-1-i];
		if(sum > maxsum) maxsum = sum;
	}
	if(n % 2)
	{
		if(data[n/2]*2 > maxsum) maxsum = data[n/2]*2;
	}

	double mid = maxsum;
	mid/=2;
	printf("%.1lf\n",mid);
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

