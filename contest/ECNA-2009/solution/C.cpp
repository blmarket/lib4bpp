#include <iostream>
#include <string>
using namespace std;

const int MAXSIZE = 1000;

struct entry {
	string s;
	int val;
};

entry dict[MAXSIZE];
int ndict;

int getNum(string &s, int size)
{
	int ans = 0;
	int n = size;
	do {
		if (s.size() == 0) {
			return -1;
		}
		ans = 10*ans + s[0] - '0';
		s = s.substr(1,s.size());
		n /= 10;
	} while (n >= 1);
	if (ans > size)
		return -1;
	return ans;
}

int main()
{
	string s;
	int i, j, n, icase=0;
	cin >> s;
	while (s != "0") {
		icase++;
		cin >> n;
		for(ndict=0; ndict<n; ndict++) {
			cin >> dict[ndict].s;
			dict[ndict].val = ndict;
		}

		string ans = "";
		bool first = true;
		while (s.length() > 0) {
			i = getNum(s, ndict-1);
			if (i < 0) {
				ans = "Error in decompression";
				break;
			}
			if (!first) {
				dict[ndict-1].s += dict[i].s[0];
			}
			else
				first = false;
			ans += dict[i].s;
			dict[ndict].s = dict[i].s;
			dict[ndict].val = ndict++;
		}
		cout << "Case " << icase << ": " << ans << endl;
			
		cin >> s;
	}
	return 0;
}
