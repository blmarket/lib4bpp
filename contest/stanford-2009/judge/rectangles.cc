#include <iostream>
#include <set>
#include <vector>
#include <algorithm>

using namespace std;

struct Box {
  int x1, y1, x2, y2, L;

  Box(int x1, int y1, int x2, int y2) :
    x1(x1), y1(y1), x2(x2), y2(y2), L(1) {}
  
  bool operator<(const Box &rhs) const {
    return make_pair(y1, x1) < make_pair(rhs.y1, rhs.x1);
  }
};

int main() {
  int n;
  while (cin >> n) {    
    if (n == 0) break;

    // read input        
    vector<Box> boxes;
    for (size_t i = 0; i < n; i++) {
      int x1, y1, x2, y2;
      cin >> x1 >> y1 >> x2 >> y2;
      boxes.push_back(Box(x1, y1, x2, y2));
    }
    
    sort(boxes.begin(), boxes.end());
    for (size_t i = 0; i < boxes.size(); i++) {
      for (size_t j = 0; j < i; j++) {
	if (boxes[j].x2 < boxes[i].x1 && boxes[j].y2 < boxes[i].y1) 
	  boxes[i].L = max(boxes[i].L, boxes[j].L + 1);
      }
    }

    // compute answer
    int best = 0;
    for (size_t i = 0; i < boxes.size(); i++)
      best = max(best, boxes[i].L);

    cout << best << endl;
  }
  
  return 0;
}
