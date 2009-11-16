#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <cmath>
#include <sstream>
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

int n,m;
int data[105][105];
bool visit[105][105];

const int dx[] = {-1,0,0,1};
const int dy[] = {0,-1,1,0};

bool check(int x,int y)
{
	return x>=0 && y>=0 && x<n && y<m;
}

void dfs(int a,int b,int c)
{
	if(visit[a][b]) return;
	visit[a][b]=true;
	for(int i=0;i<4;i++)
	{
		int nx = a + dx[i];
		int ny = b + dy[i];
		if(check(nx,ny) == false) continue;
		if(data[nx][ny] <= c)
			dfs(nx,ny,c);
	}
}

bool process(int tcase)
{
	memset(data,0,sizeof(data));
	scanf("%d %d",&n,&m);
	if(n==0 && m==0) return true;
	for(int i=0;i<n;i++)
	{
		for(int j=0;j<m;j++)
		{
			scanf("%d",&data[i][j]);
		}
	}

	for(int i=1;i<=1000;i++)
	{
		memset(visit,0,sizeof(visit));
		for(int j=0;j<n;j++)
		{
			for(int k=0;k<m;k++) if(visit[j][k] == false)
			{
				if(data[j][k] <= i && (j==0 || k==0 || j==n-1 || k==m-1)) 
				{  
					dfs(j,k,i); 
				}
			}
		}

		bool checks = false;
		for(int j=0;j<n;j++)
		{
			for(int k=0;k<m;k++)
			{
				if(!visit[j][k])
				{
					if(checks)
					{
						printf("Case %d: Island splits when ocean rises %d feet.\n",tcase,i);
						return false;
					}
					else
					{
						dfs(j,k,2000);
						checks=true;
					}
				}
			}
		}
	}
	printf("Case %d: Island never splits.\n",tcase);
	return false;
}

int main(void)
{
	for(int i=1;;i++)
	{
		if(process(i)) break;
	}
}

