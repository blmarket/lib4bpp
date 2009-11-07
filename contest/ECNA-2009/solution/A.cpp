#include <iostream>
using namespace std;

int results[9216];		// max possible results
int nr;

void operatorOrder(int [], int);

void operandOrder(int a[], int n)
{
	if (n == 1) {
		results[nr++] = a[0];
	}
	else {
		for(int i=0; i<n; i++) {
			int temp = a[0];
			a[0] = a[i];
			a[i] = temp;
			for(int j=1; j<n; j++) {
				temp = a[1];
				a[1] = a[j];
				a[j] = temp;
				operatorOrder(a, n);
				temp = a[1];
				a[1] = a[j];
				a[j] = temp;
			}
			temp = a[0];
			a[0] = a[i];
			a[i] = temp;
		}
	}
}

void operatorOrder(int a[], int n)
{
	int a0 = a[0];
	int a1 = a[1];
	a[1] = a[n-1];
	a[0] = a0+a1;
	operandOrder(a, n-1);
	a[0] = a0-a1;
	operandOrder(a, n-1);
	a[0] = a0*a1;
	operandOrder(a, n-1);
	if (a1 != 0 && a0 % a1 == 0) {
		a[0] = a0/a1;
		operandOrder(a, n-1);
	}
	a[n-1] = a[1];
	a[1] = a1;
	a[0] = a0;
}

void sort(int a[], int nr)
{
	for(int i=1; i<nr; i++) {
		int sav = a[i];
		int j=i;
		while (j>0 && a[j-1]>sav) {
			a[j] = a[j-1];
			j--;
		}
		a[j] = sav;
	}
}

void output(int a[], int nr)
{
	int maxCount=0, saveFirst, saveLast;
	int count = 1;
	int first = a[0];
	for(int i=1; i<nr; i++) {
		if (a[i]-a[i-1] == 1)
			count++;
		else if (a[i]-a[i-1] > 1) {
			if (count >= maxCount) {
				maxCount = count;
				saveFirst = first;
				saveLast = a[i-1];
			}
			first = a[i];
			count = 1;
		}
	}
	if (count >= maxCount) {
		maxCount = count;
		saveFirst = first;
		saveLast = a[nr-1];
	}
	cout << saveFirst << " to " << saveLast << endl;
}

int main()
{
	int vals[4];
	int icase=0;
	cin >> vals[0] >> vals[1] >> vals[2] >> vals[3];
	while (vals[0] != 0) {
		icase++;
		cout << "Case " << icase << ": ";
		nr=0;
		operandOrder(vals, 4);
		sort(results, nr);
		output(results, nr);
		cin >> vals[0] >> vals[1] >> vals[2] >> vals[3];
	}
}

