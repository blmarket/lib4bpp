#include <iostream>
#include <algorithm>
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
typedef long long LL;

template<typename T> inline int size(const T &a) { return a.size(); }
template<typename T> inline bool operator<(const int &a,const vector<T> &b) { return a<b.size(); }

bool process(void)
{
	string str;
	getline(cin,str);

	int pos = 0;

	while(true)
	{
		pos = str.find("What is", pos);
		if(pos == -1) break;
		pos += 4;
		int pos2 = str.find("?", pos+1);
		int pos3 = str.find(".", pos+1);
		if(pos2 == -1) break;
		if(pos3!=-1 && pos3 < pos2)
		{
			pos=pos3+1;
			continue;
		}
		cout << "Forty-two" << str.substr(pos, pos2-pos) << "." << endl;
		pos = pos2+1;
	}

	str="";
	getline(cin,str);
	if(str != "") while(true);
	return false;
}

int main(void)
{
	while(process());
}

