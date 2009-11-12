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

bool process(int tcase)
{
	string encoded;
	cin >> encoded;
	if(encoded == "0") return false;
	int n;
	cin >> n;
	vector<string> dict(n);
	for(int i=0;i<n;i++)
	{
		cin >> dict[i];
	}

	int len=1, maxdic=10;
	while(dict.size() > maxdic)
		len++, maxdic *= 10;

	string ret;
	
	for(int i=0;i<size(encoded);i+=len)
	{
		if(dict.size() > maxdic)
			len++, maxdic*=10;
		string cur = encoded.substr(i,len);

		string next="";
		if(i+len < size(encoded))
		{
			next = encoded.substr(i+len, len + ((dict.size()==maxdic)?1:0));
		}

		int curcode=0, nextcode=0;
		istringstream(cur) >> curcode;
		istringstream(next) >> nextcode;

		if(curcode >= dict.size())
			while(true);

		ret += dict[curcode];

		if(nextcode > dict.size())
		{
			cerr << encoded << endl;
			while(true);
			int tt = 1/0;
		}

		string dic = dict[curcode];
		if(nextcode == dict.size())
			dic += dict[curcode][0];
		else
			dic += dict[nextcode][0];

		dict.pb(dic);
	}

	cout << "Case " << tcase << ": " << ret << endl;

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

