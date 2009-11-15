#include <cctype>
#include <iostream>
#include <string>

using namespace std;

int main() {
	string word;
	string buf;

	bool fresh = true;

	while(cin >> word, cin) {
		if(fresh) {
			buf = "Forty-two ";
			fresh = false;
			continue;
		}
		if(word[word.size() - 1] == '.') {
			fresh = true;
			continue;
		}
		if(word[word.size() - 1] == '?') {
			buf += word.substr(0, word.size() - 1) + ".";
			cout << buf << endl;
			fresh = true;
			continue;
		}
		buf += word + " ";
	}

	return 0;
}
