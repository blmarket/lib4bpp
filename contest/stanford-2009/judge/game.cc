#include <iostream>
#include <vector>
#include <string>

using namespace std;

string msgs[2] = { "Carl can't win", "Carl can win" };

int main() {
	int N;
	while(cin >> N, N) {
		vector<int> inputs(20);
		int winnable;
		int shift = 0;
		int k;

		for(int i=0; i<20; i++) {
			cin >> k;
			if((i+1+k) % 21)
				shift = 1;
		}

		if(N % 21)
			winnable = 1;
		else if(N == 21)
			winnable = 0;
		else
			winnable = shift;

		cout << msgs[winnable] << endl;
	}

	return 0;
}
