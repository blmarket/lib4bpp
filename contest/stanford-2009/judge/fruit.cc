#include <iostream>
#include <algorithm>
#include <vector>
#include <cmath>
#include <cassert>

using namespace std;

double INF = 1e100;
double EPS = 1e-12;

struct PT { 
  double x, y; 
  PT() {}
  PT(double x, double y) : x(x), y(y) {}
  PT(const PT &p) : x(p.x), y(p.y)    {}
  PT operator + (const PT &p)  const { return PT(x+p.x, y+p.y); }
  PT operator - (const PT &p)  const { return PT(x-p.x, y-p.y); }
  PT operator * (double c)     const { return PT(x*c,   y*c  ); }
  PT operator / (double c)     const { return PT(x/c,   y/c  ); }
};

double dot(PT p, PT q)     { return p.x*q.x+p.y*q.y; }
double dist2(PT p, PT q)   { return dot(p-q,p-q); }
double cross(PT p, PT q)   { return p.x*q.y-p.y*q.x; }
ostream &operator<<(ostream &os, const PT &p) {
  os << "(" << p.x << "," << p.y << ")"; 
}

// rotate a point CCW or CW around the origin
PT RotateCCW90(PT p)   { return PT(-p.y,p.x); }
PT RotateCW90(PT p)    { return PT(p.y,-p.x); }

// project point c onto line segment through a and b
PT ProjectPointSegment(PT a, PT b, PT c) {
  double r = dot(b-a,b-a);
  if (fabs(r) < EPS) return a;
  r = dot(c-a, b-a)/r;
  if (r < 0) return a;
  if (r > 1) return b;
  return a + (b-a)*r;
}

// determine if lines from a to b and c to d are parallel or collinear
bool LinesParallel(PT a, PT b, PT c, PT d) { 
  return fabs(cross(b-a, c-d)) < EPS; 
}

bool LinesCollinear(PT a, PT b, PT c, PT d) { 
  return LinesParallel(a, b, c, d) && fabs(cross(a-c, d-c)) < EPS; 
}

// determine if line segment from a to b intersects with 
// line segment from c to d
bool SegmentsIntersect(PT a, PT b, PT c, PT d) {
  if (LinesCollinear(a, b, c, d)) {
    if (dist2(a, c) < EPS || dist2(a, d) < EPS ||
      dist2(b, c) < EPS || dist2(b, d) < EPS) return true;
    if (dot(c-a, c-b) > 0 && dot(d-a, d-b) > 0 && dot(c-b, d-b) > 0)
      return false;
    return true;
  }
  if (cross(d-a, b-a) * cross(c-a, b-a) > 0) return false;
  if (cross(a-c, d-c) * cross(b-c, d-c) > 0) return false;
  return true;
}

// compute intersection of line passing through a and b
// with line passing through c and d, assuming that unique
// intersection exists; for segment intersection, check if
// segments intersect first
PT ComputeLineIntersection(PT a, PT b, PT c, PT d) {
  b=b-a; d=c-d; c=c-a;
  assert(dot(b, b) > EPS && dot(d, d) > EPS);
  return a + b*cross(c, d)/cross(b, d);
}

// compute center of circle given three points
PT ComputeCircleCenter(PT a, PT b, PT c) {
  b=(a+b)/2;
  c=(a+c)/2;
  return ComputeLineIntersection(b, b+RotateCW90(a-b), c, c+RotateCW90(a-c));
}

// determine if point is in a possibly non-convex polygon (by William
// Randolph Franklin); returns 1 for strictly interior points, 0 for
// strictly exterior points, and 0 or 1 for the remaining points.
// Note that it is possible to convert this into an *exact* test using
// integer arithmetic by taking care of the division appropriately
// (making sure to deal with signs properly) and then by writing exact
// tests for checking point on polygon boundary
bool PointInPolygon(const vector<PT> &p, PT q) {
  bool c = 0;
  for (int i = 0; i < p.size(); i++){
    int j = (i+1)%p.size();
    if ((p[i].y <= q.y && q.y < p[j].y || 
      p[j].y <= q.y && q.y < p[i].y) &&
      q.x < p[i].x + (p[j].x - p[i].x) * (q.y - p[i].y) / (p[j].y - p[i].y))
      c = !c;
  }
  return c;
}

// determine if point is on the boundary of a polygon
bool PointOnPolygon(const vector<PT> &p, PT q) {
  for (int i = 0; i < p.size(); i++)
    if (dist2(ProjectPointSegment(p[i], p[(i+1)%p.size()], q), q) < EPS)
      return true;
    return false;
}

// compute intersection of line through points a and b with
// circle centered at c with radius r > 0
vector<PT> CircleLineIntersection(PT a, PT b, PT c, double r) {
  vector<PT> ret;
  b = b-a;
  a = a-c;
  double A = dot(b, b);
  double B = dot(a, b);
  double C = dot(a, a) - r*r;
  double D = B*B - A*C;
  if (D < -EPS) return ret;
  ret.push_back(c+a+b*(-B+sqrt(D+EPS))/A);
  if (D > EPS)
    ret.push_back(c+a+b*(-B-sqrt(D))/A);
  return ret;
}

// compute intersection of circle centered at a with radius r
// with circle centered at b with radius R
vector<PT> CircleCircleIntersection(PT a, PT b, double r, double R) {
  vector<PT> ret;
  double d = sqrt(dist2(a, b));
  if (d > r+R || d+min(r, R) < max(r, R)) return ret;
  double x = (d*d-R*R+r*r)/(2*d);
  double y = sqrt(r*r-x*x);
  PT v = (b-a)/d;
  ret.push_back(a+v*x + RotateCCW90(v)*y);
  if (y > 0)
    ret.push_back(a+v*x - RotateCCW90(v)*y);
  return ret;
}

/////////////////////////////////////////////////

bool operator<(const PT &p, const PT &q) { return make_pair(p.y,p.x) < make_pair(q.y,q.x); }
const double R = 1.0, SEPS = sqrt(EPS);

void Add(const vector<PT> &chosen, vector<PT> &new_events, const vector<PT> &tri, const vector<PT> &p) {
  for (size_t i = 0; i < p.size(); i++) {
    double min_y = chosen.size() ? chosen.back().y : -INF;
    bool valid = p[i].y >= min_y - SEPS && 
      (PointInPolygon(tri, p[i]) || PointOnPolygon(tri, p[i]));
    for (int j = int(chosen.size()) - 1; valid && j >= 0; j--) {
      if (chosen[j].y < p[i].y - 2*R - SEPS) break;
      if (dist2(p[i], chosen[j]) < 4*R*R - SEPS) valid = false;      
    }
    if (valid) new_events.push_back(p[i]);
  }
}

int main() {
  double a, b, h;
  
  while (cin >> a >> b >> h) {
    if (a == 0) break;
    a *= M_PI/180.0;
    b *= M_PI/180.0;

    vector<PT> chosen;        // maintains a list of included circles, sorted by y then x
    vector<PT> events;        // maintains a list of potential circles for inclusion, sorted by y then x
    vector<PT> new_events;

    // edges of feasible region
    pair<PT,PT> left(PT(R*cos(a), R*sin(a)), PT(R*cos(a) - h*tan(a), R*sin(a) + h));
    pair<PT,PT> right(PT(-R*cos(b), R*sin(b)), PT(-R*cos(b) + h*tan(b), R*sin(b) + h));
    pair<PT,PT> top(PT(-h*tan(a), h-R), PT(h*tan(b), h-R));

    // create feasible region
    vector<PT> tri;
    tri.push_back(ComputeLineIntersection(left.first, left.second, right.first, right.second));
    tri.push_back(ComputeLineIntersection(right.first, right.second, top.first, top.second));
    tri.push_back(ComputeLineIntersection(top.first, top.second, left.first, left.second));

    // add initial event
    if (tri[0].y < h-R + SEPS) Add(chosen, events, tri, vector<PT>(1, tri[0]));

    while (events.size()) {
      PT p = events[0];
      //cerr << chosen.size() + 1 << " " << p << endl;
      chosen.push_back(p);
      new_events.clear();

      // copy over old events
      for (size_t i = 1; i < events.size(); i++)
	if (dist2(p, events[i]) > 4*R*R-EPS) new_events.push_back(events[i]);
      
      // create new events
      Add(chosen, new_events, tri, CircleLineIntersection(left.first, left.second, p, 2*R));
      Add(chosen, new_events, tri, CircleLineIntersection(right.first, right.second, p, 2*R));
      for (int i = int(chosen.size()) - 2; i >= 0; i--) {
	if (chosen[i].y < p.y - 2*R - SEPS) break;
	Add(chosen, new_events, tri, CircleCircleIntersection(p, chosen[i], 2*R, 2*R));
      }
      sort(new_events.begin(), new_events.end());
      new_events.swap(events);
    }
    cout << chosen.size() << endl;
  }
  return 0;
}
