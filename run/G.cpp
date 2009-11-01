#include <iostream>
#include <complex>
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
typedef complex<double> point;

template<typename T> int size(const T &a) { return a.size(); }

vector<point> V;

double area(const point &cur, const point &next)
{
	double xdiff = cur.real() - next.real();
	double y1 = cur.imag();
	double y2 = next.imag();
	return (y1+y2)*xdiff;
}

void process(void)
{
	int n;
	scanf("%d",&n);
	V.clear();
	for(int i=0;i<n;i++)
	{
		double x,y;
		scanf("%lf %lf",&x,&y);
		V.pb(point(x,y));
	}

	vector<double> ax(n,0);

	for(int i=0;i<n;i++)
	{
		const point &v1 = V[i];
		for(int j=i+1;j<n;j++)
		{
			const point &v2 = V[j];
			for(int k=j+1;k<n;k++)
			{
				const point &v3 = V[k];
				double tmp = area(v1,v2) + area(v2,v3) + area(v3,v1);
				if(tmp < 0) tmp*=-1;
				ax[i] += tmp;
				ax[j] += tmp;
				ax[k] += tmp;
			}
		}
	}

	double maxx = 0;
	double sum = 0;
	for(int i=0;i<n;i++)
	{
		sum += ax[i];
		if(maxx < ax[i]) maxx = ax[i];
	}
	sum -= maxx*3;

	int count = (n-1)*(n-2)*(n-3)/2;
	double result = ((sum / count)+1.0)/2.0;
	int rr = (int)(result);
	cout << rr << endl;
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

