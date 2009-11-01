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
	int n,m;
	scanf("%d %d",&n,&m);
	VVI data(n,VI(m));
	vector<bool> avail(n,false);
	for(int i=0;i<n;i++)
	{
		for(int j=0;j<m;j++)
		{
			scanf("%d",&data[i][j]);
		}
	}

	for(int i=0;i<m;i++)
	{
		vector<int> V;
		V.clear();
		int mint = 100;
		for(int j=0;j<n;j++) if(avail[j] == false)
		{
			if(data[j][i] < mint)
			{
				mint = data[j][i];
				V.clear();
			}
			if(data[j][i] == mint)
			{
				V.pb(j);
			}
		}
		if(V.size() > 1)
		{
			for(int j=0;j<V.size();j++)
				cout << V[j]+1 << " ";
			cout << endl;
			return;
		}
		avail[V[0]]=true;
	}

	for(int i=0;i<n;i++)
	{
		if(avail[i] == false)
		{
			cout << i+1 << " ";
		}
	}
	cout << endl;
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

