import java.util.Scanner;


public class Leapfrog {
  static int[] arr = new int[1 << 20];
  
  public static void main(String[] args) {
    Scanner s = new Scanner(System.in);
    while (true) {
      int n = s.nextInt();
      if (n == 0) break;
      for (int i = 0; i < n; i++) {
        arr[i] = s.nextInt();
      }
      int back = 0;
      int front = 1;
      int count = 0;
      boolean ok = true;
      while (front < n - 1) {
        count++;
        if (arr[n - 1] <= arr[back] + 10) break;
        int next = front + 1;
        while (arr[next] <= arr[back] + 10) next++;
        next--;
        if (arr[next + 1] > arr[front] + 10) next--;
        if (next <= front) {
          ok = false;
          break;
        }
        back = front;
        front = next;
      }
      
      if (!ok) {
        System.out.println(-1);
      } else {
        System.out.println(count);
      }
    }
  }
}
