import java.util.Arrays;
import java.util.Scanner;


public class Rectangles {
  static class Rect implements Comparable<Rect> {
    int x1, x2, y1, y2;

    @Override
    public int compareTo(Rect o) {
      if (this.x1 == o.x1) return this.y1 - o.y1;
      return this.x1 - o.x1;
    }
  }
  
  static Rect[] arr = new Rect[1024];
  static int[] len = new int[1024];
  
  public static void main(String[] args) {
    Scanner s = new Scanner(System.in);
    while (true) {
      int n = s.nextInt();
      if (n == 0) break;
      for (int i = 0; i < n; i++) {
        arr[i] = new Rect();
        arr[i].x1 = s.nextInt();
        arr[i].y1 = s.nextInt();
        arr[i].x2 = s.nextInt();
        arr[i].y2 = s.nextInt();
      }
      
      Arrays.sort(arr, 0, n);
      
      for (int i = 0; i < n; i++) {
        len[i] = 1;
        for (int j = 0; j < i; j++) {
          if (arr[j].x2 < arr[i].x1 && arr[j].y2 < arr[i].y1) {
            len[i] = Math.max(len[i], len[j] + 1);
          }
        }
      }
      
      int best = 0;
      for (int i = 0; i < n; i++) best = Math.max(best, len[i]);
      System.out.println(best);
    }
  }
}
