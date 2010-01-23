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

vector<vector<bool> > init;

const int dx[] = {-1,0,0,1};
const int dy[] = {0,-1,1,0};

bool check(const vector<vector<bool> > &board,int x,int y)
{
	return x>=0 && y>=0 && x<board.size() && y<board[0].size();
}

bool move(vector<vector<bool> > &state, int &x,int &y,int dir)
{
	bool canmove = false;
	while(true)
	{
		int nx = x + dx[dir];
		int ny = y + dy[dir];
		if(check(state,nx,ny) && state[nx][ny] == false)
		{
			canmove=true;
			state[nx][ny]=true;
			x=nx;
			y=ny;
		}
		else
		{
			break;
		}
	}
	return canmove;
}

bool go(vector<vector<bool> > state,int x,int y)
{
	bool flag=false;
	for(int i=0;i<state.size();i++)
	{
		for(int j=0;j<state[i].size();j++)
		{
			if(state[i][j] == false) { flag=true; break; }
		}
	}
	if(flag == false) return true;

	for(int i=0;i<4;i++)
	{
		vector<vector<bool> > tmp = state;
		int tx,ty;
		tx=x;ty=y;
		if(move(tmp,tx,ty,i))
		{
			if(go(tmp,tx,ty))
			{
				cout << i << endl;
				return true;
			} 
		}
	}
	return false;
}

void process(void)
{
	int n,m;

	scanf("%d %d",&n,&m);
	init.clear();
	init.resize(n,vector<bool>(m,false));

	for(int i=0;i<n;i++)
	{
		for(int j=0;j<m;j++)
		{
			int tmp;
			scanf("%d",&tmp);
			if(tmp) init[i][j]=true;
		}
	}

	for(int i=0;i<n;i++)
	{
		for(int j=0;j<m;j++)
		{
			if(init[i][j] == false)
			{
				init[i][j]=true;
				if(go(init,i,j))
				{
					cout << i << " " << j << endl;
					return;
				}
				init[i][j]=false;
			}
		}
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

