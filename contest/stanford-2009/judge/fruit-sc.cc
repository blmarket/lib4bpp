// --------------------------------------------------------------------------
// SLPC2009 - Fruit Bowl solution (hopefully correct!)
//
// Author:  Sonny Chan
// Date:    October 1, 2009
// --------------------------------------------------------------------------

#include <iostream>
#include <algorithm>
#include <vector>
#include <list>
#include <queue>
#include <cmath>

using namespace std;

const double EPSILON = 1e-10;

struct point {
    double x, y;
    point(double xx = 0.0, double yy = 0.0) : x(xx), y(yy) {}
};
typedef point vect;

struct line {
    point p;
    vect d;
    line(const point &origin = point(), const vect &direction = vect(1,0))
    : p(origin), d(direction) {}
};

bool operator<(const point &a, const point &b)
{
    if (a.y == b.y) return a.x > b.x;
    return a.y > b.y;
}

ostream &operator<<(ostream &stream, const point &p)
{
    stream << '(' << p.x << ", " << p.y << ')';
    return stream;
}

vect operator+(const vect &a, const vect &b) {
    return vect(a.x+b.x, a.y+b.y);
}

vect operator-(const vect &a, const vect &b) {
    return vect(a.x-b.x, a.y-b.y);
}

vect operator*(double s, const vect &v) {
    return vect(s*v.x, s*v.y);
}

double dot(const vect &a, const vect &b) {
    return a.x*b.x + a.y*b.y;
}

vect unit(const vect &v) {
    return (1.0 / sqrt(dot(v,v))) * v;
}

vect perp(const vect &v) {
    return vect(-v.y, v.x);
}

bool leftof(const line &l, const point &p) {
    return dot(p-l.p, perp(l.d)) > -EPSILON;
}

point intersection(const line &a, const line &b)
{
    point e = b.p - a.p;
    double k = a.d.x * b.d.y - a.d.y * b.d.x;
    double s = (e.x * b.d.y - e.y * b.d.x) / k;
    return a.p + s*a.d;
}

double distance2(const point &p, const line &l)
{
    vect v = p - l.p;
    double t = dot(l.d, v);
    return dot(v, v) - t*t;
}

double distance2(const point &a, const point &b)
{
    vect v = b-a;
    return dot(v, v);
}

struct bowl
{
    int fruit;
    line la, lb;
    double height;
    
    priority_queue<point> candidates;
    
    vector< vector< list<point> > > cells;
    int offsetx, offsety;
    
    int cellx(const point &p) { return int(0.5*p.x) + offsetx; }
    int celly(const point &p) { return int(0.5*p.y) + offsety; }
    
    // constructor
    bowl(double A, double B, double H) : fruit(0)
    {
        // save height, offset by radius 1.0
        height = H - 1.0;
        
        // compute the edge lines, offset by radius 1.0
        double ta = A * M_PI / 180.0;
        double tb = B * M_PI / 180.0;
        vect da = vect(sin(ta), -cos(ta));
        vect db = vect(sin(tb),  cos(tb));
        la = line(perp(da), da);
        lb = line(perp(db), db);
        
        // create the cells that store our fruit
        int cy = 0.5 * height + 7;
        int cx = 2 * cy * tan(max(ta, tb)) + 7;
        offsetx = cx/2;
        offsety = 2;
        cells = vector< vector< list<point> > >(cy, vector< list<point> >(cx));
    }
    
    // find the fruit that rests (higher) on two other fruit
    point supported(point a, point b)
    {
        if (b.x < a.x) swap(a, b);
        vect d = b - a;
        double base2 = dot(d,d) / 4.0;
        double h = base2 < 4.0 ? sqrt(4.0 - base2) : 0.0;
        return 0.5*(a+b) + h*unit(perp(d));
    }
    
    // find the fruit that rests (higher) on a fruit and a wall
    point supported(point a, line w)
    {
        vect v = a - w.p;
        double t = dot(w.d, v);
        double h2 = dot(v, v) - t*t;
        double b = h2 < 4.0 ? sqrt(4.0 - h2) : 0.0;
        if (w.d.y > 0.0)    return w.p + (t+b)*w.d;
        else                return w.p + (t-b)*w.d;
    }
    
    // test if a fruit can be placed in the bowl
    bool test(const point &p)
    {
        // check if point is in the bowl first
        if (!leftof(la, p)) return false;
        if (!leftof(lb, p)) return false;
        
        // check for collisions with other fruit
        int cx = cellx(p);
        int cy = celly(p);
        for (int y = cy-1; y <= cy+1; ++y)
            for (int x = cx-1; x <= cx+1; ++x) {
                list<point> &lp = cells[y][x];
                for (list<point>::iterator it = lp.begin(); it != lp.end(); ++it)
                    if (distance2(p, *it) < 4.0-EPSILON) return false;
            }
        
        return true;
    }
    
    // put a fruit in the bowl at position p
    void place(const point &p)
    {
        int cx = cellx(p);
        int cy = celly(p);
        
        // generate candidate locations for fruit that can rest on this one
        if (distance2(p, la) < 4.0) candidates.push(supported(p, la));
        if (distance2(p, lb) < 4.0) candidates.push(supported(p, lb));
        
        for (int y = cy-2; y <= cy+2; ++y)
            for (int x = cx-2; x <= cx+2; ++x) {
                list<point> &lp = cells[y][x];
                for (list<point>::iterator it = lp.begin(); it != lp.end(); ++it)
                    if (distance2(p, *it) < 16.0) candidates.push(supported(p, *it));
            }
        
        // then still the fruit in its cell
        cells[cy][cx].push_back(p);
        ++fruit;
    }
    
    // fetch the next potential location for a fruit
    point next()
    {
        point p;
        if (candidates.empty())
            p = intersection(la, lb);
        else {
            p = candidates.top();
            candidates.pop();
        }
        return p;
    }
    
    // fill the fruit bowl
    int fill()
    {
        for (;;) {
            point p = next();
            if (p.y > height) break;
            if (test(p)) place(p);
        }
        return fruit;
    }
};

int main()
{
    double A, B, H;
    while (cin >> A >> B >> H)
    {
        if (A == 0) break;
        bowl b(A, B, H);
        int n = b.fill();
        cout << n << endl;
    }
    
    return 0;
}
