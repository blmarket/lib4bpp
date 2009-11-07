#include <iostream>
using namespace std;

const int SIZE = 10;
const int MAXNUM = 6;


bool bestStrat[SIZE];
int bestStratSize = 0;

double calcProb(int n, bool correct[], bool strategy[], int num[], int likely[], double prob[])
{
	double ans = 1.0, p;
	for(int i=0; i<n; i++) {
		if (strategy[i]) {
			if (likely[i] == 0)
				p = 0.0;
			else
				p = prob[i]/likely[i];
		}
		else {
			if (num[i]-likely[i] == 0)
				p = 0;
			else
				p = (1.0-prob[i])/(num[i]-likely[i]);
		}
		if (correct[i]) {
			ans *= p;
		}
		else
			ans *= (1.0-p);
	}
	return ans;
}

double bestStrategy(int n, int num[], int likely[], double prob[], int level);

double evalStrategy(int n, bool strategy[], int num[], int likely[], double prob[], int level)
{
	int num2[SIZE], likely2[SIZE];
	double prob2[SIZE];
	int n2=0;
	double total = 1.0;
	bool correct[SIZE];


	int count = 1;
	for(int i=0; i<n; i++) {
		if (strategy[i] && likely[i] == 0)
			return 0.0;
		if ((!strategy[i]) && (num[i]-likely[i] == 0))
			return 0.0;
		correct[i] = true;
		count *= 2;
	}
	total = calcProb(n, correct, strategy, num, likely, prob);		// get prob of all correct

	count -= 2;						// skip all correct and all incorrect cases in loop
	for(;count>0; count--) {
		int i=0;
		while (!correct[i]) {
			correct[i] = true;
			i++;
		}
		correct[i] = false;
		double thisProb = calcProb(n, correct, strategy, num, likely, prob);
		if (thisProb != 0) {
			int j=0;
			for(int k=0; k<n; k++) {
				if (!correct[k]) {
					num2[j] = num[k] - 1;
					if (strategy[k]) {
						likely2[j] = likely[k] - 1;
						prob2[j] = prob[k]*(likely[k]-1)/(likely[k]-prob[k]);
					}
					else {
						likely2[j] = likely[k];
						prob2[j] = prob[k]*(num[k]-likely[k])/(num[k]-likely[k]-(1.0-prob[k]));
					}
					j++;
				}
			}
			total += thisProb*bestStrategy(j, num2, likely2, prob2, level+1);
		}
	}
	return total;
}

double bestStrategy(int n, int num[], int likely[], double prob[], int level)
{
	double best = 0.0, curr;
	bool strategy[SIZE];

	for(int i=0; i<n; i++) {
		strategy[i] = true;
	}

	while(true) {
		curr = evalStrategy(n, strategy, num, likely, prob, level);
		if (curr >= best) {
			best = curr;
			if (level==0) {
				bestStratSize = n;
				for(int i=0;i<n;i++)
					bestStrat[i] = strategy[i];
			}
		}
		int i=0;
		while (i<n && !strategy[i]) {
			strategy[i] = true;
			i++;
		}
		if (i == n)
			break;
		strategy[i] = false;
	}
	return best;
}

int main()
{
	int n;
	int num[SIZE], likely[SIZE];
	double prob[SIZE];

	cin >> n;
	while (n != 0) {
		for(int i=0; i<n; i++) {
			cin >> num[i] >> likely[i] >> prob[i];
		}
		double ans = bestStrategy(n, num, likely, prob, 0);
		ans = ((int)(1000*ans+0.5))/1000.0;
		cout << ans << endl;;
		cin >> n;
	}
}
