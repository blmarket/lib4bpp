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

vector<PII> data;

void process(void)
{
	int n,m;
	scanf("%d %d",&n,&m);
	data.resize(m);
	for(int i=0;i<m;i++)
	{
		scanf("%d %d",&data[i].second, &data[i].first);
		data[i].second--;
	}
	sort(data.begin(),data.end());

	VI pos(n,-1);
	pos[0]=0;

	for(int i=0;i<m;i++)
	{
		int aa = data[i].second;
		if(pos[aa] == -1)
		{
			if(pos[aa+1] == -1)
				continue;
			pos[aa] = pos[aa+1];
			pos[aa+1] = pos[aa+1]+1;
		}
		else
		{
			if(pos[aa+1] == -1)
			{
				pos[aa+1] = pos[aa];
				pos[aa] = pos[aa]+1;
			}
			else
			{
				int aaa,bbb;
				aaa = min(pos[aa]+1,pos[aa+1]);
				bbb = min(pos[aa],pos[aa+1]+1);
				pos[aa] = aaa;
				pos[aa+1] = bbb;
			}
		}
	}

	cout << pos[n-1] << endl;
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

