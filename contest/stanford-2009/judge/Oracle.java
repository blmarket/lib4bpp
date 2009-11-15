import java.util.Scanner;
import java.util.regex.Matcher;
import java.util.regex.Pattern;

public class Oracle {
  public static void main(String[] args) {
    Scanner s = new Scanner(System.in);
    String str = s.nextLine();
    Pattern p = Pattern.compile("What( is[ a-z\\-,;\\']*)\\?");
    Matcher m = p.matcher(str);
    while (m.find()) {
      System.out.println("Forty-two" + m.group(1) + ".");
    }
  }
}
