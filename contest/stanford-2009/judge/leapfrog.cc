#include <iostream>
#include <vector>

using namespace std;

int BiggestStep(const vector<int> &x, int p) {
  int k = p + 1;
  while (k < int(x.size()) && x[k] <= x[p] + 10) k++;
  return k - 1;
}

int main() {
  int n;

  while (cin >> n) {
    if (n == 0) break;
    
    // read input
    vector<int> x;
    for (int i = 0; i < n; i++) {
      int y;
      cin >> y;
      x.push_back(y);
    }

    // solve problem
    int hops = 0;
    int p = 0, q = 1;
    while (x[p] < x[n-1] && x[q] < x[n-1]) {
      ++hops;

      int new_p = BiggestStep(x, p);
      if (x[new_p] >= x[n-1]) break;
      int new_q = BiggestStep(x, q);

      p = q;
      q = min(new_p, new_q - 1);
      if (q <= p) {
	hops = -1;
	break;
      }
    }
    cout << hops << endl;
  }
  return 0;
}
