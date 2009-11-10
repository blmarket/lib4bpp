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

struct state
{
	state(int x,int y,int z) : x(x),y(y),z(z) {}
	int x,y,z;
};

vector<int> xdic,ydic,zdic;
map<int,int> xmap,ymap,zmap;
VVI data;

vector<vector<vector<int> > > zwall, cells;

bool check(int x,int y,int z)
{
	return x>=0 && y>=0 && z>=0 && x<size(xdic) && y<size(ydic) && z<size(zdic);
}

bool checkx(int x,int y,int z)
{
	if(zwall[z][x][y] & 1)
	{
		zwall[z][x][y] |= (1<<4);
		return false;
	}
	return true;
}

bool checky(int x,int y,int z)
{
	if(zwall[z][x][y] & 2)
	{
		zwall[z][x][y] |= (1<<5);
		return false;
	}
	return true;
}

bool checkz(int x,int y,int z)
{
	if(zwall[z][x][y] & 4)
	{
		zwall[z][x][y] |= (1<<6);
		return false;
	}
	return true;
}

const int dx[] = {-1,0,0,1,0,0};
const int dy[] = {0,-1,0,0,1,0};
const int dz[] = {0,0,-1,0,0,1};

bool checkit(int x,int y,int z,int dir)
{
	switch(dir)
	{
	case 0:
		if(x==0) return false;
		return checkx(x,y,z);
	case 1:
		if(y==0) return false;
		return checky(x,y,z);
	case 2:
		if(z==0) return false;
		return checkz(x,y,z);
	case 3:
		if(x==size(xdic)-1) return false;
		return checkx(x+1,y,z);
	case 4:
		if(y==size(ydic)-1) return false;
		return checky(x,y+1,z);
	case 5:
		if(z==size(zdic)-1) return false;
		return checkz(x,y,z+1);
	}
	return false;
}

void addzwall(int z,int x0,int y0,int x1,int y1)
{
	VVI &tgt = zwall[z];
	for(int i=x0;i<x1;i++)
		for(int j=y0;j<y1;j++)
			tgt[i][j] |= (1<<2);
}

void addxwall(int x,int y0,int z0,int y1,int z1)
{
	for(int i=z0;i<z1;i++)
	{
		for(int j=y0;j<y1;j++)
		{
			zwall[i][x][j] |= (1<<0);
		}
	}
}

void addywall(int y,int x0,int z0,int x1,int z1)
{
	for(int i=z0;i<z1;i++)
	{
		for(int j=x0;j<x1;j++)
		{
			zwall[i][j][y] |= (1<<1);
		}
	}
}

void makemap(const VI &a, map<int,int> &b)
{
	b.clear();
	for(int i=0;i<size(a);i++) b[a[i]]=i;
}

void process(void)
{
	VI init;
	init.pb(-100);
	init.pb(1500);
	xdic=ydic=zdic=init;

	int n;
	scanf("%d",&n);
	data.resize(n,VI(6,0));
	for(int i=0;i<n;i++)
	{
		for(int j=0;j<6;j++)
			cin >> data[i][j];
		xdic.pb(data[i][0]);
		xdic.pb(data[i][0]+data[i][3]);
		ydic.pb(data[i][1]);
		ydic.pb(data[i][1]+data[i][4]);
		zdic.pb(data[i][2]);
		zdic.pb(data[i][2]+data[i][5]);

		data[i][3] += data[i][0];
		data[i][4] += data[i][1];
		data[i][5] += data[i][2];
	}

	sort(xdic.begin(),xdic.end());
	sort(ydic.begin(),ydic.end());
	sort(zdic.begin(),zdic.end());
	xdic.erase(unique(xdic.begin(),xdic.end()),xdic.end());
	ydic.erase(unique(ydic.begin(),ydic.end()),ydic.end());
	zdic.erase(unique(zdic.begin(),zdic.end()),zdic.end());

	makemap(xdic,xmap);
	makemap(ydic,ymap);
	makemap(zdic,zmap);

	zwall.clear();
	zwall.resize(zdic.size(), VVI(size(xdic), VI(size(ydic))));
	cells = zwall;

	for(int i=0;i<n;i++)
	{
		data[i][0] = xmap[data[i][0]];
		data[i][1] = ymap[data[i][1]];
		data[i][2] = zmap[data[i][2]];
		data[i][3] = xmap[data[i][3]];
		data[i][4] = ymap[data[i][4]];
		data[i][5] = zmap[data[i][5]];

		addxwall(data[i][0],data[i][1],data[i][2],data[i][4],data[i][5]);
		addxwall(data[i][3],data[i][1],data[i][2],data[i][4],data[i][5]);
		addywall(data[i][1],data[i][0],data[i][2],data[i][3],data[i][5]);
		addywall(data[i][4],data[i][0],data[i][2],data[i][3],data[i][5]);
		addzwall(data[i][2],data[i][0],data[i][1],data[i][3],data[i][4]);
		addzwall(data[i][5],data[i][0],data[i][1],data[i][3],data[i][4]);
	}

	int nx=size(xdic),ny=size(ydic),nz=size(zdic);

	queue<state> Q;
	Q.push(state(0,0,0));
	zwall[0][0][0] |= (1<<3);

	while(!Q.empty())
	{
		state st = Q.front();
		Q.pop();
		int x=st.x;
		int y=st.y;
		int z=st.z;

		for(int i=0;i<6;i++)
		{
			if(checkit(x,y,z,i))
			{
				int nx,ny,nz;
				nx = x+dx[i];
				ny = y+dy[i];
				nz = z+dz[i];
				if(zwall[nz][nx][ny] & (1<<3)) continue;
				zwall[nz][nx][ny] |= (1<<3);
				Q.push(state(nx,ny,nz));
			}
		}
	}

	long long area=0,volume=0;

	for(int i=0;i<nz-1;i++)
	{
		for(int j=0;j<nx-1;j++)
		{
			for(int k=0;k<ny-1;k++)
			{
				if((zwall[i][j][k] & (1<<3)) == 0)
				{
					volume += (long long)(zdic[i+1]-zdic[i]) * (xdic[j+1]-xdic[j]) * (ydic[k+1]-ydic[k]);
				}

				if((zwall[i][j][k] & (1<<4))) // xwall
				{
					area += (long long)(zdic[i+1] - zdic[i]) * (ydic[k+1]-ydic[k]);
				}
				if((zwall[i][j][k] & (1<<5)))
				{
					area += (long long)(zdic[i+1] - zdic[i]) * (xdic[j+1]-xdic[j]);
				}
				if((zwall[i][j][k] & (1<<6)))
				{
					area += (long long)(xdic[j+1]-xdic[j]) * (ydic[k+1]-ydic[k]);
				}
			}
		}
	}

	cout << area << " " << volume << endl;
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

