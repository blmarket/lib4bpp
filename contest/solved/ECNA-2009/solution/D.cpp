#include <iostream>
using namespace std;

const int MAX = 100;

struct card
{
	int val;
	bool up;
} cards[MAX];
int ileft, iright;

void print(int n)
{
	for(int i=0; i<n; i++) {
		cout << cards[i].val;
		if (cards[i].up)
			cout << 'U';
		else
			cout << 'D';
		cout << ' ';
	}
	cout << endl;
}

int main()
{
	int n, m;
	int ipile = 0;

	cin >> n;
	while (n > 0) {
		ipile++;
		for(int i=0; i<n; i++) {
			char ch;
			cin >> ch;
			cards[i].val = i+1;
			cards[i].up = (ch == 'U');
		}
		ileft = 0;
		iright = n-1;

		char ch;
		for(int i=0; i<n-1; i++) {
			cin >> ch;
			if (ch == 'L') {
				for(int j=0; j<=ileft/2; j++) { 
					card c = cards[j];
					cards[j] = cards[ileft-j];
					cards[ileft-j] = c;
				}
				for(int j=0; j<=ileft; j++)
					cards[j].up = !cards[j].up;
				ileft++;
			}
			else {
				int k=n-1;
				int j=iright;
				while (j < k) {
					card c = cards[j];
					cards[j] = cards[k];
					cards[k] = c;
					j++;
					k--;
				}
				for(int j=iright; j<n; j++)
					cards[j].up = !cards[j].up;
				iright--;
			}
		}
		if (ch == 'L') {
			int k=n-1;
			int j=iright;
			while (j < k) {
				card c = cards[j];
				cards[j] = cards[k];
				cards[k] = c;
				j++;
				k--;
			}
		}
		else {
			for(int j=0; j<=ileft/2; j++) {
				card c = cards[j];
				cards[j] = cards[ileft-j];
				cards[ileft-j] = c;
			}
			for(int j=0; j<=(n-1)/2; j++) {
				card c = cards[j];
				cards[j] = cards[n-1-j];
				cards[n-1-j] = c;
			}
		}

		cout << "Pile " << ipile << endl;
		cin >> m;
		for(int i=0; i<m; i++) {
			int index;
			cin >> index;
			cout << "Card " << index << " is a face ";
			if (cards[index-1].up)
				cout << "up ";
			else
				cout << "down ";
			cout << cards[index-1].val << "." << endl;
		}

		cin >> n;
	}

}
