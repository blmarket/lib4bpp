#include <iostream>
#include <cmath>
using namespace std;

const int MAXSIZE = 5000;

long matrix[MAXSIZE][MAXSIZE];
int rows, cols;

int rowFactors[100];
int colFactors[100];
int nr, nc;

long gcd(long a, long b)
{
	if (b == 0)
		return a;
	else
		return gcd(b, a%b);
}

void calcFactors(int val, int factors[], int &num)
{
	num = 0;
	int f = 1;
	while (f <= val/2) {
		if (val%f == 0)
			factors[num++] = f;
		f++;
	}
	factors[num++] = val;
}

long calcFactors(long val)
{
	long num = 0;
	long f = 1;
	long sq = (long) sqrt((double) val);
	while (f <= sq) {
		if (val%f == 0)
			num+=2;
		f++;
	}
	f--;
	if (f*f == val)
		num--;
	return num;
}

int isTensor(int r, int c)
{
	if (r==1 && c==1)
		return false;
	if (r==rows && c==cols)
		return false;
	int i, j, k, l;
	long val1 = matrix[0][0];
	long gcd1 = matrix[0][0];
	for(i=0; i<rows/r; i++) {
		for(j=0; j<cols/c; j++) {
			long val2 = matrix[i*r][j*c];
			for(k=0; k<r; k++) {
				for(l=0; l<c; l++) {
					gcd1 = gcd(gcd1, matrix[k][l]);
					if (val1*matrix[i*r+k][j*c+l] != val2*matrix[k][l])
						return 0;
				}
			}
		}
	}
	int baseVal = matrix[0][0]/gcd1;
	for(i=0; i<rows; i+=r)
		for(j=0; j<cols; j+=c) {
			gcd1 = gcd(gcd1, matrix[i][j]/baseVal);
		}

	return calcFactors(gcd1);
}

int main()
{
	int i, j;

	cin >> rows >> cols;
	while (rows != 0) {
		for(i=0; i<rows; i++) {
			for(j=0; j<cols; j++) {
				cin >> matrix[i][j];
			}
		}

		calcFactors(rows, rowFactors, nr);
		calcFactors(cols, colFactors, nc);

		int numTensor=0;
		for(i=0; i<nr; i++) {
			for(j=0; j<nc; j++) {
				numTensor += isTensor(rowFactors[i], colFactors[j]);
			}
		}
		cout << numTensor << endl;

		cin >> rows >> cols;
	}
}
