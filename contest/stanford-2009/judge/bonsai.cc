#include <iostream>
#include <vector>

using namespace std;

typedef pair<int, int> PII;
typedef vector<PII> VPII;
typedef vector<VPII> VVPII;
typedef vector<int> VI;

const int INF = 1000000000;

int CutSubtree(const VVPII &tree, VI &seen, int r) {
  seen[r] = true;
  int totcost = 0;
  bool isleaf = true;

  for (size_t i = 0; i < tree[r].size(); i++) {
    if (seen[tree[r][i].first]) continue;
    totcost += min(tree[r][i].second, CutSubtree(tree, seen, tree[r][i].first));
    isleaf = false;
  }

  if (isleaf) return INF;
  return totcost;
}

int main() {
  int n, r;
  while (cin >> n >> r) {
    if (n == 0 && r == 0) break;
    r--;
    
    VVPII tree(n);
    for (int i = 0; i < n-1; i++) {
      int u, v, w;
      cin >> u >> v >> w;
      u--; v--;
      tree[u].push_back(make_pair(v, w));
      tree[v].push_back(make_pair(u, w));
    }

    VI seen(n);    
    cout << (n == 1 ? 0 : CutSubtree(tree, seen, r)) << endl;
  }
  
  return 0;
}
