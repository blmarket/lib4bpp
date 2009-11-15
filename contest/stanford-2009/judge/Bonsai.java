import java.util.Arrays;
import java.util.Scanner;


public class Bonsai {
  static int[][] arc = new int[1024][1024];
  static int[] cost = new int[1024];
  static int[] order = new int[1024];
  static boolean[] leaf = new boolean[1024];
  static boolean[] visited = new boolean[1024];
  static int pos;
  static int n;
  
  public static void main(String[] args) {
    Scanner s = new Scanner(System.in);
    while (true) {
      n = s.nextInt();
      int r = s.nextInt();
      if (n == 0) break;
      for (int i = 0; i < 1024; i++) Arrays.fill(arc[i], -1);
      for (int i = 0; i < n - 1; i++) {
        int u = s.nextInt();
        int v = s.nextInt();
        int w = s.nextInt();
        arc[u][v] = arc[v][u] = w;
      }
      
      Arrays.fill(leaf, false);
      Arrays.fill(visited, false);
      pos = 0;
      topSort(r);
      
      for (int i = 0; i < n; i++) {
        int cur = order[i];
        if (leaf[cur] && cur != r) {
          cost[i] = Integer.MAX_VALUE;
        } else {
          cost[i] = 0;
          for (int j = 0; j < i; j++) {
            if (arc[order[j]][cur] > -1) {
              cost[i] += Math.min(arc[order[j]][cur], cost[j]);
            }
          }
        }
      }
      
      System.out.println(cost[n - 1]);
    }
  }
  
  static void topSort(int node) {
    if (visited[node]) return;
    visited[node] = true;
    int count = 0;
    for (int i = 1; i <= n; i++) {
      if (arc[node][i] > -1) {
        topSort(i);
        count++;
      }
    }
    if (count == 1) leaf[node] = true;
    order[pos++] = node;
  }
}
