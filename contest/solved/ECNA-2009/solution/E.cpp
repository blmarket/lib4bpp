#include <iostream>
using namespace std;

const int MAX = 100;

struct mapsq {
	int height;
	int pass;
	bool sub;
} map[MAX+2][MAX+2];

int vals[MAX*MAX];
int nvals;
int startx, starty;

bool find(int v, int low, int high, int& index)
{
	if (high == -1 || low == high) {
		index = low;
		return vals[low] == v;
	}
	int mid = (low+high)/2;
	if (v <= vals[mid])
		return find(v, low, mid, index);
	else
		return find(v, mid+1, high, index);
}

void insert(int v, int r, int c)
{
	int index;
	if (nvals == 0) {
		vals[0] = v;
		nvals = 1;
		return;
	}
	if (!find(v, 0, nvals-1, index)) {
		for(int i=nvals; i>index+1; i--)
			vals[i] = vals[i-1];
		if (vals[index] > v) {
			vals[index+1] = vals[index];
			index--;
		}
		vals[index+1] = v;
		nvals++;
	}
}

int countSubmerged(int wh, int row, int col, int n, int m)
{
	if (row < 0 || row > n+1 || col < 0 || col > m+1)
		return 0;
	if (map[row][col].pass > 0)
		return 0;
	map[row][col].pass = 1;
	if (map[row][col].height > wh) {
		startx = row;
		starty = col;
		return 0;
	}
	map[row][col].sub = true;
	return 1 + countSubmerged(wh, row+1, col, n, m) + countSubmerged(wh, row, col+1, n, m)
			 + countSubmerged(wh, row-1, col, n, m) + countSubmerged(wh, row, col-1, n, m);
}

int search(int row, int col)
{
	if (map[row][col].pass > 1)
		return 0;
	map[row][col].pass = 2;
	if (map[row][col].sub)
		return 0;
	return 1 + search(row+1, col) + search(row, col+1)
			 + search(row-1, col) + search(row, col-1);
}

int main()
{
	int n, m, icase=0;
	cin >> n >> m;
	while ( n > 0) {
		icase++;
		nvals = 0;
		for(int i=1; i<=n; i++) {
			map[i][0].height = 0;
			for(int j=1; j<=m; j++) {
				cin >> map[i][j].height;
				map[i][j].pass = -1;
				insert(map[i][j].height, i, j);
			}
			map[i][m+1].height = 0;
		}
		for(int j=0; j<=m+1; j++) {
			map[0][j].height = 0;
			map[n+1][j].height = 0;
		}

		int iv=0;
		while (iv<nvals-1) {
			int wheight = vals[iv];
			for(int i=0; i<n+2; i++)
				for(int j=0; j<m+2; j++) {
					map[i][j].sub = false;
					map[i][j].pass = 0;
				}
			int count = countSubmerged(wheight, 0, 0, n, m);
			int count2 = search(startx, starty);
			if (count2 + count != (n+2)*(m+2))
				break;
			iv++;
		}
		cout << "Case " << icase << ": ";
		if (iv < nvals-1)
			cout << "Island splits when ocean rises " << vals[iv] << " feet." << endl;
		else
			cout << "Island never splits." << endl;

		cin >> n >> m;
	}
}
