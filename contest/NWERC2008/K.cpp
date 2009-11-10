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

int score[9];
const char* nums = "A23456789TJQK";
const char* types = "sdhc";
vector<string> hand;
VI hv;
int perm[5];
int ncount[32];
long long totscore[32];
int nnums[13];
int ntypes[4];

int calc_score(void)
{
	bool flush = false;
	for(int i=0;i<4;i++) if(ntypes[i] == 5) flush = true;

	if(flush) // royal flush, straight flush, flush
	{
		int incr = 0;
		bool straight = false, royal = false;
		for(int i=0;i<13;i++)
		{
			if(nnums[i]) incr++; else incr=0;
			if(incr == 5) { straight = true; break; }
		}
		if(incr == 4 && nnums[0] == 1) royal = straight = true;

		if(royal) return score[8];
		if(straight) return score[7];
	}

	int nx[5] = {0};
	for(int i=0;i<13;i++)
		nx[nnums[i]]++;
	if(nx[4]) return score[6];
	if(nx[3] && nx[2]) return score[5];
	if(flush) return score[4];

	{
		int incr = 0;
		bool straight = false;
		for(int i=0;i<13;i++)
		{
			if(nnums[i]) incr++; else incr=0;
			if(incr == 5) { straight = true; break; }
		}
		if(incr == 4 && nnums[0] == 1) straight = true;

		if(straight) return score[3];
	}

	if(nx[3]) return score[2];
	if(nx[2] == 2) return score[1];
	if(nx[2]) return score[0];
	return 0;
}

void permute(int a,int b,int c,int mask)
{
	if(a==5)
	{
		ncount[mask]++;
		totscore[mask] += calc_score();
		return;
	}
	for(int i=b;i<52;i++)
	{
		int n1 = i / 4;
		int n2 = i % 4;
		nnums[n1]++;
		ntypes[n2]++;
		perm[a] = i;
		if(i == hv[c])
		{
			permute(a+1,i+1,c+1,mask | (1<<c));
			c++;
		}
		else
		{
			permute(a+1,i+1,c,mask);
		}
		nnums[n1]--;
		ntypes[n2]--;
	}
}

void process(void)
{
	int n;
	for(int i=0;i<9;i++)
		scanf("%d",&score[i]);
	scanf("%d",&n);
	for(int i=0;i<n;i++)
	{
		hand.resize(5);
		hv.resize(5);
		for(int j=0;j<5;j++)
		{
			cin >> hand[j];
			for(int k=0;k<13;k++) if(hand[j][0] == nums[k])
			{
				for(int l=0;l<4;l++)
				{
					if(hand[j][1] == types[l])
					{
						hv[j] = k*4+l;
						break;
					}
				}
			}
		}

		sort(hv.begin(),hv.end());
		memset(ncount,0,sizeof(ncount));
		memset(totscore,0,sizeof(totscore));
		permute(0,0,0,0);
		double maxscore = 0;
		for(int i=0;i<32;i++)
		{
			double tmp = (double)totscore[i] / ncount[i];
			if(maxscore < tmp) maxscore = tmp;
		}
		printf("%.8lf\n",maxscore);
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

