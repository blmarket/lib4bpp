import java.awt.geom.Line2D;
import java.awt.geom.Point2D;
import java.util.ArrayList;
import java.util.Comparator;
import java.util.Scanner;
import java.util.TreeSet;

public class Fruit {
  static Point2D.Double[] centers = new Point2D.Double[1 << 20];
  static double a, b, h;
  static int last, cur;
  static Point2D.Double a1, a2, b1, b2;
  static Line2D.Double wa, wb;
  
  public static void main(String[] args) throws Exception {
    Scanner s = new Scanner(System.in);
    while (true) {
      a = s.nextInt() * Math.PI / 180; 
      b = s.nextInt() * Math.PI / 180; 
      h = s.nextInt(); 
      if (a == 0) break;
      a1 = new Point2D.Double(0, 0);
      a2 = new Point2D.Double(-h * Math.tan(a), h);
      wa = new Line2D.Double(a1, a2);
      a1.x += Math.cos(a); a1.y += Math.sin(a);
      a2.x += Math.cos(a); a2.y += Math.sin(a);
      b1 = new Point2D.Double(0, 0);
      b2 = new Point2D.Double(h * Math.tan(b), h);
      wb = new Line2D.Double(b1, b2);
      b1.x -= Math.cos(b); b1.y += Math.sin(b);
      b2.x -= Math.cos(b); b2.y += Math.sin(b);
      
      centers[0] = LLI(a1, a2, b1, b2);
      
      last = cur = 0;
      TreeSet<Point2D.Double> queue = new TreeSet<Point2D.Double>(new Comparator<Point2D.Double>() {
        public int compare(Point2D.Double o1, Point2D.Double o2) {
          return o1.y == o2.y ? (o1.x == o2.x ? 0 : o1.x < o2.x ? -1 : 1) : o1.y < o2.y ? -1 : 1;
        }
      });
      
      for (Point2D.Double p : CLI(a1, a2, centers[0], 2)) queue.add(p);
      for (Point2D.Double p : CLI(b1, b2, centers[0], 2)) queue.add(p);
      
      while (centers[cur].y <= h - 1) {
        Point2D.Double best = queue.first();
        queue.remove(best);
        while (centers[last].y < centers[cur].y - 2) last++;
        cur++;
        if (!isValid(best)) {cur--; continue;}
        centers[cur] = best;
        for (Point2D.Double temp : queue) {
          if (Math.abs(best.y - temp.y) < 1e-5) {
            if (Math.abs(best.x - temp.x) > 1e-5 && isValid(temp)) {
              System.out.println("WARNING: " + best + ", " + temp);
            }
          } else {
            break;
          }
        } 
        
        for (Point2D.Double p : CLI(a1, a2, best, 2)) queue.add(p);
        for (Point2D.Double p : CLI(b1, b2, best, 2)) queue.add(p);
        for (int i = last; i < cur; i++) {
          for (Point2D.Double p : CCI(best, centers[i], 2, 2)) queue.add(p);
        }
      }

      if (cur > 0 && Math.abs(centers[cur - 1].y - h + 1) < 1e-2) {
        System.out.println("WARNING:" + centers[cur - 1]);
      }
      if (Math.abs(centers[cur].y - h + 1) < 1e-2) {
        System.out.println("WARNING:" + centers[cur]);
      }
      System.out.println(cur);
    }
  }
  
  
  static boolean isValid(Point2D.Double p) {
    if (p.y < centers[cur - 1].y) return false;
    for (int i = last; i < cur; i++) {
      if (centers[i].distanceSq(p) < 4 - 1e-10) {
        return false;
      }
    }
    if (wa.ptLineDistSq(p) < 1 - 1e-10) return false;
    if (wb.ptLineDistSq(p) < 1 - 1e-10) return false;
    return true;
  }
  
  static ArrayList<Point2D.Double> CLI(Point2D.Double a, Point2D.Double b, Point2D.Double c, double r) {
    ArrayList<Point2D.Double> ret = new ArrayList<Point2D.Double>();
    Point2D.Double bb = new Point2D.Double(b.x-a.x, b.y-a.y);
    Point2D.Double aa = new Point2D.Double(a.x-c.x, a.y-c.y);
    double A = bb.x * bb.x + bb.y * bb.y;
    double B = aa.x * bb.x + aa.y * bb.y;
    double C = aa.x * aa.x + aa.y * aa.y - r*r;
    double D = B*B - A*C;
    if (D < 0) return ret;
    ret.add(new Point2D.Double(c.x+aa.x+bb.x*(-B+Math.sqrt(D))/A, c.y+aa.y+bb.y*(-B+Math.sqrt(D+1e-10))/A));
    if (D > 0)
      ret.add(new Point2D.Double(c.x+aa.x+bb.x*(-B-Math.sqrt(D))/A, c.y+aa.y+bb.y*(-B-Math.sqrt(D))/A));
    return ret;
  }
  
  static Point2D.Double LLI(Point2D.Double a, Point2D.Double b, Point2D.Double c, Point2D.Double d) {
    Point2D.Double B = new Point2D.Double(b.x-a.x, b.y-a.y);
    Point2D.Double D = new Point2D.Double(c.x-d.x, c.y-d.y);
    Point2D.Double C = new Point2D.Double(c.x-a.x, c.y-a.y);
    double mult = (C.x*D.y-C.y*D.x)/(B.x*D.y-B.y*D.x);
    return new Point2D.Double(a.x + B.x*mult, a.y + B.y*mult);
  }

  static ArrayList<Point2D.Double> CCI(Point2D.Double a, Point2D.Double b, double r, double R) {
    ArrayList<Point2D.Double> ret = new ArrayList<Point2D.Double>();
    double d = a.distance(b);
    if (d > r+R || d+Math.min(r, R) < Math.max(r, R)) return ret;
    double x = (d*d-R*R+r*r)/(2*d);
    double y = Math.sqrt(r*r-x*x);
    Point2D.Double v = new Point2D.Double((b.x - a.x)/d, (b.y - a.y)/d);
    ret.add(new Point2D.Double(a.x + x*v.x - y*v.y, a.y + x*v.y + y*v.x));
    if (y > 0) ret.add(new Point2D.Double(a.x + x*v.x + y*v.y, a.y + x*v.y - y*v.x));
    return ret;
  }
}
