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

set<pair<string,int> > memo;

struct state
{
	state(string str,int pos,int move) : str(str),pos(pos),move(move) {}

	string str;
	int pos;
	int move;

	bool operator< (const state &a) const
	{
		return move > a.move;
	}
};

int checkback(string str,int pos)
{
	for(int i=pos-1;i>0;i--)
	{
		if(str[i] != 'B')
		{
			if(str[i-1] == 'B' || str[i-1] == 'E') 
			{
				return i-1;
			}
			return -1;
		}
	}
	return -1;
}

int makemove(state st, vector<state> &ret)
{
	string str = st.str;
	int tmp = checkback(str,st.pos);
	if(tmp != -1)
	{
		char tc = str[tmp];
		str[tmp] = 'B';
		ret.pb(state(str,tmp,st.move+1));
		str[tmp] = tc;
	}
	for(int i=st.pos+1;i<size(str);i++)
	{
		if(str[i] != 'B')
		{
			if(str[i+1] == 'F')
			{ // no move
				return 0;
			}
			if(str[i+1] == 'K')
			{ // cool
				return 1;
			}
			if(str[i+1] == 'E')
			{
				str[i+1] = 'B';
				ret.pb(state(str,i+1,st.move+1));
				return 0;
			}
			if(str[i+1] == 'B')
			{
				ret.push_back(state(str,i+1,st.move+1));
				for(int j=i+2;j<size(str);j++)
				{
					switch(str[j])
					{
						case 'K':
							return 1;
						case 'F':
							return 0;
						case 'E':
							str[j]='B';
							ret.pb(state(str,j,st.move+1));
							return 0;
					}
				}
				return 0;
			}
		}
	}
	return 0;
}

void encode(string &str, int &pos)
{
	int kpos = str.find('K');
	if(kpos < pos)
	{
		reverse(str.begin(),str.end());
		pos = size(str)-1-pos;
		kpos = size(str)-1-kpos;
	}

	for(int i=pos-1;i>=0;i--)
	{
		if(str[i] == 'B') continue;
		if(i>0)
		{
			if(str[i-1] == 'E' || str[i-1] == 'B')
			{
				str = "BF" + str.substr(pos);
				pos = 2;
				return;
			}
			else
			{
				return;
			}
		}
		else
		{
			str = str[0] + str.substr(pos);
			pos=1;
			return;
		}
	}
}

void process(void)
{
	string str;
	cin >> str;

	int spos=-1;
	for(int i=0;i<size(str);i++) if(str[i] == 'C')
	{
		spos = i;
		str[i] = 'B';
		break;
	}

	encode(str,spos);

	queue<state> Q;
	memo.clear();
	memo.insert(mp(str,spos));

	Q.push(state(str,spos,0));

	while(!Q.empty())
	{
		state st = Q.front();
		Q.pop();
//		cout << st.str << " " << st.pos << " " << st.move << endl;

		vector<state> next;
		next.clear();

		if(makemove(st,next))
		{
			cout << st.move+1 << endl;
			return;
		}

		for(int i=0;i<next.size();i++)
		{
			encode(next[i].str, next[i].pos);
			pair<string,int> key = mp(next[i].str,next[i].pos);
			if(memo.count(key)) continue;
			memo.insert(key);
			Q.push(next[i]);
		}
	}
	cout << 0 << endl;
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

