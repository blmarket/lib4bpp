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
	vector<long long> V;
	int n;
	cin >> n;
	V.resize(n);
	for(int i=0;i<n;i++)
		cin >> V[i];

	if(n <= 2)
	{
		cout << "0" << endl;
		return;
	}

	for(int a=0;a<10001;a++)
	{
		int b=0;
		(a * V[0] + b) * a + b;
		a*a*V[0]+a*b+b==V[1];
		(a+1)*b==V[1]-a*a*V[0];

		long long tmp = (V[1] + 10001 - ((a*a*V[0])%10001))%10001;
		for(int b=0;b<10001;b++)
		{
			if( (((a+1)*b)%10001)  == tmp)
			{
				bool correct = true;
				for(int i=1;i<size(V)-1;i++)
				{
					long long tmp = (a*a*V[i]+a*b+b)%10001;
					if(tmp != V[i+1])
					{
						correct=false;
						break;
					}
				}
				if(correct)
				{
					for(int i=0;i<size(V);i++)
					{
						cout << (a*V[i]+b)%10001 << endl;
					}
					return;
				}
			}
		}
	}
}

int main(void)
{
	process();
}

