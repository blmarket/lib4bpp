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
	int s,n;
	scanf("%d %d",&s,&n);
	vector<int> cnts(s,0);
	vector<bool> check(s,true);
	int n2 = 0;
	int n3 = 0;

	queue<int> Q;
	for(int i=0;i==0 || Q.empty()==false;i++)
	{
		int tmp;
		if(i<n)
		{
			scanf("%d",&tmp);
			tmp--;
			Q.push(tmp);
			cnts[tmp]++;
			if(cnts[tmp] == 2)
				n2++;
			if(cnts[tmp] == 3)
				n3++;
		}

		if(i >= s)
		{
			int tmp2 = Q.front();
			Q.pop();
			cnts[tmp2]--;
			if(cnts[tmp2] == 1)
				n2--;
		}

		check[i%s] = check[i%s] && (n2==0);
	}
	
	if(n3)
	{
		cout << 0 << endl;
		return;
	}

	int cnt=0;
	for(int i=0;i<size(check);i++)
		cnt += check[i];
	if(cnt == n)
		cout << s << endl;
	else
		cout << cnt << endl;
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

