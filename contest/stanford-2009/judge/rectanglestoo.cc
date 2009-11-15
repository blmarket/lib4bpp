#include <iostream>
#include <set>
#include <vector>
#include <algorithm>

using namespace std;

struct Box {
  int x1, y1, x2, y2, L;

  Box(int x1, int y1, int x2, int y2) :
    x1(x1), y1(y1), x2(x2), y2(y2), L(1) {}
};

bool LowerComparator(const Box *a, const Box *b) {
  return make_pair(a->y1, a->x1) < make_pair(b->y1, b->x1);
}

bool UpperComparator(const Box *a, const Box *b) {
  return make_pair(a->y2, a->x2) < make_pair(b->y2, b->x2);
}

int main() {
  int n;
  while (cin >> n) {    
    if (n == 0) break;

    // read input        
    vector<Box> boxes;
    set<int> ys;
    for (size_t i = 0; i < n; i++) {
      int x1, y1, x2, y2;
      cin >> x1 >> y1 >> x2 >> y2;
      boxes.push_back(Box(x1, y1, x2, y2));
      ys.insert(boxes[i].y1);
      ys.insert(boxes[i].y2);
    }
    
    // sort boxes by lower and upper y's
    vector<Box *> lower(n);
    for (int i = 0; i < n; i++) lower[i] = &boxes[i];
    vector<Box *> upper = lower;
        
    sort(lower.begin(), lower.end(), LowerComparator);
    sort(upper.begin(), upper.end(), UpperComparator);
    int lower_pos = 0;
    int upper_pos = 0;
    
    // maintain "active set" of chains; each chain is represented as a
    // pair (x2, L) where x2 is the ending x-coordinate of the last
    // block in the chain, and L is the number of blocks in the chain;
    // the active set maintains the invariant that it is strictly
    // increasing in both x and L at all points in the algorithm
    set<pair<int, int> > active;
    
    // considering increasing y coordinates
    for (set<int>::iterator y_iter = ys.begin(); y_iter != ys.end(); ++y_iter) {
      const int y = *y_iter;
      
      // find best parents for all boxes beginning with this y value
      while (lower_pos < lower.size() && lower[lower_pos]->y1 == y) {
	Box *box = lower[lower_pos++];

	set<pair<int, int> >::iterator iter = active.lower_bound(make_pair(box->x1, 0));
	if (iter == active.begin()) {
	  box->L = 1;
	} else {
	  --iter;
	  box->L = iter->second + 1;
	} 
      }
      
      // add all boxes ending with this y value to the active set
      while (upper_pos < upper.size() && upper[upper_pos]->y2 == y) {
	const Box *box = upper[upper_pos++];
	const pair<int, int> p(box->x2, box->L);
	
	// check if this box should be skipped
	set<pair<int, int> >::iterator start_iter = active.upper_bound(p);
	if (start_iter != active.begin()) {
	  set<pair<int, int> > ::iterator iter = start_iter;
	  --iter;
	  if (iter->second >= box->L) continue;
	}
	
	// remove boxes that would be made obsolete
	set<pair<int, int> >::iterator end_iter = start_iter;
	while (end_iter != active.end() && end_iter->second <= box->L) ++end_iter;
	active.erase(start_iter, end_iter);
	
	// insert box
	active.insert(p);
      }
    }

    // compute answer
    int best = 0;
    for (int i = 0; i < n; i++)
      best = max(best, boxes[i].L);

    cout << best << endl;
  }
  
  return 0;
}
