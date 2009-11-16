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

struct box
{
	int x,y,w,h;

	bool check(int xx,int yy)
	{
		if(xx < x || yy < y) return false;
		if(xx >= x+h || yy >= y+w) return false;
		return true;
	}
};

template<typename T> T& operator>>(T &a, box &b)
{
	a >> b.x >> b.y >> b.w >> b.h;
}

bool process(int tcase)
{
	int n;
	vector<box> V;
	cin >> n;
	if(n==0) return false;
	V.resize(n);
	for(int i=0;i<n;i++) cin >> V[i];
	int m;
	cin >> m;

	cout << "Desktop " << tcase << ":" << endl;
	for(int i=0;i<m;i++)
	{
		int x,y;
		cin >> x >> y;
		bool found = false;
		for(int j=size(V)-1;j>=0;j--)
		{
			if(V[j].check(x,y))
			{
				cout << "window " << j+1 << endl;
				found=true;
				break;
			}
		}
		if(!found)
		{
			cout << "background" << endl;
		}
	}
	return true;
}

int main(void)
{
	for(int i=1;;i++)
    {
        if(!process(i)) break;
    }
	return 0;
}

