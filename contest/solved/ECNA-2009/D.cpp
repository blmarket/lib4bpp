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

void process(void)
{
}

vector<vector<int> > stack;

int main(void)
{
	for(int Tcase=1;;Tcase++)
	{
		stack.clear();
		int n;
		string str1,str2;
		cin >> n;
		if(n == 0) break;
		cin >> str1;

		stack.resize(n);
		for(int i=0;i<size(str1);i++)
		{
			if(str1[i] == 'U')
			{
				stack[i].pb(i+1);
			}
			else
			{
				stack[i].pb(-i-1);
			}
		}

		cin >> str2;

		for(int i=0;i<size(str2);i++)
		{
			if(str2[i] == 'L')
			{
				while(stack[0].size())
				{
					stack[1].pb(-stack[0].back());
					stack[0].pop_back();
				}

				stack.erase(stack.begin(),stack.begin()+1);
			}
			else
			{
				while(stack.back().size())
				{
					stack[stack.size()-2].pb(-stack.back().back());
					stack.back().pop_back();
				}
				stack.pop_back();
			}
		}

		int m;
		printf("Pile %d\n",Tcase);
		cin >> m;
		for(int j=0;j<m;j++)
		{
			int tmp;
			cin >> tmp;
			int pos = stack[0].size() - tmp;
			printf("Card %d is a face ",tmp);
			if(stack[0][pos] < 0)
				printf("down ");
			else
				printf("up ");
			printf("%d.\n",abs(stack[0][pos]));
		}
	}
	return 0;
}

