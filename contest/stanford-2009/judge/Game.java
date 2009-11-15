import java.util.Scanner;

public class Game {
  public static void main(String[] args) {
    Scanner s = new Scanner(System.in);
    while (true) {
      int N = s.nextInt();
      if (N == 0) break;
      boolean sorted = true;
      for (int i = 0; i < 20; i++) {
        if (i + s.nextInt() != 20) sorted = false;
      }
      
      if (N == 21 || (N % 21 == 0 && sorted)) {
        System.out.println("Carl can't win");
      } else {
        System.out.println("Carl can win");
      }
    }
  }
}
