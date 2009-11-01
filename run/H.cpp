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

vector<long long> mask;
vector<long long> mask2;
const int bits=30;

void process(void)
{
	mask.clear();
	mask2.clear();
	char tmp1[200005],tmp2[200005];
	scanf("%s",tmp1);
	int len1 = strlen(tmp1);
	scanf("%s",tmp2);
	int len2 = strlen(tmp2);
	mask.resize(len1/bits+1);
	mask2.resize(len2/bits+1);
	for(int i=0;i<len1;i++)
	{
		if(tmp1[i] == 'M')
			mask[i/bits] |= (1LL << (i%bits));
	}

	for(int i=0;i<len2;i++)
	{
		if(tmp2[i] == 'M')
			mask2[i/bits] |= (1LL << (i%bits));
	}

	int ret=0;

	cout << len1 << " " << len2 << endl;

	for(int i=0;i<=len2-len1;i++)
	{
		if((i%bits)==0)
		{
			for(int j=0;j<mask2.size()-1;j++)
				mask2[j] |= mask2[j+1]<<bits;
		}

		bool no=false;
		for(int j=0;j<mask.size();j++)
		{
			if(mask2[j] & mask[j])
			{
				no=true;
				break;
			}
		}
		if(!no)
		{
			ret++;
		}
		for(int j=0;j<mask2.size();j++)
			mask2[j]>>=1;
		if(mask2.size()>mask.size() && mask2.back() == 0) mask2.pop_back();
	}
	cout << ret << endl;
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

