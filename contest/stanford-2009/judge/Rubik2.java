import java.util.Arrays;
import java.util.Scanner;


public class Rubik2 {
  static int[] parent = new int[1 << 24];
  static char[] rotate = new char[1 << 24];
  
  static boolean printDebug = false;
  
  public static void main(String[] args) {
    precompute();
    
    if (printDebug) System.out.println("ready");
    
    Scanner s = new Scanner(System.in);
    while (true) {
      char[][] cube = new char[6][];
      for (int i = 0; i < 6; i++) {
        cube[i] = s.nextLine().toCharArray();
      }
      if (Arrays.equals(cube[0], cube[2])) break;
      cube = remap(cube);
      int index = deflate(cube);
      while (index != base) {
        System.out.print(rotate[index]);
        index = parent[index];
      }
      System.out.println();
      s.nextLine();
    }
  }
  
  static int[] queue = new int[1 << 24];
  static int head = 0;
  static int tail = 0;
  static void precompute() {
    long start = System.nanoTime();
    enqueue(base);
    rotate[base] = '*';
    while (head != tail) {
      int cur = dequeue();
//      char[][] cube = inflate(cur);
//      char[][] rotX = rotX(cube);
//      int x = deflate(rotX);
      int x = fastRotX(cur);
      if (rotate[x] == 0) {
        rotate[x] = 'X';
        parent[x] = cur;
        enqueue(x);
      }
//      char[][] rotY = rotY(cube);
//      int y = deflate(rotY);
      int y = fastRotY(cur);
      if (rotate[y] == 0) {
        rotate[y] = 'Y';
        parent[y] = cur;
        enqueue(y);
      }
//      char[][] rotZ = rotZ(cube);
//      int z = deflate(rotZ);
      int z = fastRotZ(cur);
      if (rotate[z] == 0) {
        rotate[z] = 'Z';
        parent[z] = cur;
        enqueue(z);
      }
    }
    
    long elapsed = System.nanoTime() - start;
    if (printDebug) System.out.println(elapsed);
  }
  
  static int dequeue() {
    if (head == tail) System.out.println("PROBLEM");
    int answer = queue[head++];
    if (head == queue.length) head = 0;
    return answer;
  }
  
  static void enqueue(int n) {
    queue[tail++] = n;
    if (tail == queue.length) tail = 0;
    if (head == tail) System.out.println("PROBLEM");
  }
  
  static char[][] rotX = new char[6][8];
  static char[][] rotX(char[][] cube) {
    rotX[0][2] = cube[0][2];
    rotX[0][3] = cube[2][3];
    rotX[1][2] = cube[1][2];
    rotX[1][3] = cube[3][3];
    rotX[2][0] = cube[2][0];
    rotX[2][1] = cube[2][1];
    rotX[2][2] = cube[2][2];
    rotX[2][3] = cube[4][3];
    rotX[2][4] = cube[3][4];
    rotX[2][5] = cube[2][4];
    rotX[2][6] = cube[1][3];
    rotX[2][7] = cube[2][7];
    rotX[3][0] = cube[3][0];
    rotX[3][1] = cube[3][1];
    rotX[3][2] = cube[3][2];
    rotX[3][3] = cube[5][3];
    rotX[3][4] = cube[3][5];
    rotX[3][5] = cube[2][5];
    rotX[3][6] = cube[0][3];
    rotX[3][7] = cube[3][7];
    rotX[4][2] = cube[4][2];
    rotX[4][3] = cube[3][6];
    rotX[5][2] = cube[5][2];
    rotX[5][3] = cube[2][6];
    return rotX;
  }
  
  static char[][] rotY = new char[6][8];
  static char[][] rotY(char[][] cube) {
    rotY[0][2] = cube[1][2];
    rotY[0][3] = cube[0][2];
    rotY[1][2] = cube[1][3];
    rotY[1][3] = cube[0][3];
    rotY[2][0] = cube[2][2];
    rotY[2][1] = cube[2][3];
    rotY[2][2] = cube[2][4];
    rotY[2][3] = cube[2][5];
    rotY[2][4] = cube[2][6];
    rotY[2][5] = cube[2][7];
    rotY[2][6] = cube[2][0];
    rotY[2][7] = cube[2][1];
    rotY[3][0] = cube[3][0];
    rotY[3][1] = cube[3][1];
    rotY[3][2] = cube[3][2];
    rotY[3][3] = cube[3][3];
    rotY[3][4] = cube[3][4];
    rotY[3][5] = cube[3][5];
    rotY[3][6] = cube[3][6];
    rotY[3][7] = cube[3][7];
    rotY[4][2] = cube[4][2];
    rotY[4][3] = cube[4][3];
    rotY[5][2] = cube[5][2];
    rotY[5][3] = cube[5][3];
    return rotY;
  }
  
  static char[][] rotZ = new char[6][8];
  static char[][] rotZ(char[][] cube) {
    rotZ[0][2] = cube[0][2];
    rotZ[0][3] = cube[0][3];
    rotZ[1][2] = cube[3][1];
    rotZ[1][3] = cube[2][1];
    rotZ[2][0] = cube[2][0];
    rotZ[2][1] = cube[4][2];
    rotZ[2][2] = cube[3][2];
    rotZ[2][3] = cube[2][2];
    rotZ[2][4] = cube[1][2];
    rotZ[2][5] = cube[2][5];
    rotZ[2][6] = cube[2][6];
    rotZ[2][7] = cube[2][7];
    rotZ[3][0] = cube[3][0];
    rotZ[3][1] = cube[4][3];
    rotZ[3][2] = cube[3][3];
    rotZ[3][3] = cube[2][3];
    rotZ[3][4] = cube[1][3];
    rotZ[3][5] = cube[3][5];
    rotZ[3][6] = cube[3][6];
    rotZ[3][7] = cube[3][7];
    rotZ[4][2] = cube[3][4];
    rotZ[4][3] = cube[2][4];
    rotZ[5][2] = cube[5][2];
    rotZ[5][3] = cube[5][3];
    return rotZ;
  }
  
  static char[][] remap = new char[6][8];
  static char[] mapping = new char[256];
  static String[] cubes = {"LFD", "FRD", "RBD", "ULB", "UFL", "URF", "UBR"};
  static int[][][] locs = {{{3, 1}, {3, 2}, {4, 2}},
                           {{3, 3}, {3, 4}, {4, 3}},
                           {{3, 5}, {3, 6}, {5, 3}},
                           {{0, 2}, {2, 0}, {2, 7}},
                           {{1, 2}, {2, 2}, {2, 1}},
                           {{1, 3}, {2, 4}, {2, 3}},
                           {{0, 3}, {2, 6}, {2, 5}}};
  static char[][] remap(char[][] cube) {
    mapping['.'] = '.';
    mapping[cube[5][2]] = 'D';
    mapping[cube[3][0]] = 'L';
    mapping[cube[3][7]] = 'B';
    
    for (int[][] triple : locs) {
      if ((cube[triple[0][0]][triple[0][1]] == cube[5][2] && cube[triple[1][0]][triple[1][1]] == cube[3][0])
          || (cube[triple[1][0]][triple[1][1]] == cube[5][2] && cube[triple[0][0]][triple[0][1]] == cube[3][0])) {
        mapping[cube[triple[2][0]][triple[2][1]]] = 'F';
      }
      if ((cube[triple[0][0]][triple[0][1]] == cube[5][2] && cube[triple[2][0]][triple[2][1]] == cube[3][0])
          || (cube[triple[2][0]][triple[2][1]] == cube[5][2] && cube[triple[0][0]][triple[0][1]] == cube[3][0])) {
        mapping[cube[triple[1][0]][triple[1][1]]] = 'F';
      }
      if ((cube[triple[1][0]][triple[1][1]] == cube[5][2] && cube[triple[2][0]][triple[2][1]] == cube[3][0])
          || (cube[triple[2][0]][triple[2][1]] == cube[5][2] && cube[triple[1][0]][triple[1][1]] == cube[3][0])) {
        mapping[cube[triple[0][0]][triple[0][1]]] = 'F';
      }
          
      if ((cube[triple[0][0]][triple[0][1]] == cube[5][2] && cube[triple[1][0]][triple[1][1]] == cube[3][7])
          || (cube[triple[1][0]][triple[1][1]] == cube[5][2] && cube[triple[0][0]][triple[0][1]] == cube[3][7])) {
        mapping[cube[triple[2][0]][triple[2][1]]] = 'R';
      }
      if ((cube[triple[0][0]][triple[0][1]] == cube[5][2] && cube[triple[2][0]][triple[2][1]] == cube[3][7])
          || (cube[triple[2][0]][triple[2][1]] == cube[5][2] && cube[triple[0][0]][triple[0][1]] == cube[3][7])) {
        mapping[cube[triple[1][0]][triple[1][1]]] = 'R';
      }
      if ((cube[triple[1][0]][triple[1][1]] == cube[5][2] && cube[triple[2][0]][triple[2][1]] == cube[3][7])
          || (cube[triple[2][0]][triple[2][1]] == cube[5][2] && cube[triple[1][0]][triple[1][1]] == cube[3][7])) {
        mapping[cube[triple[0][0]][triple[0][1]]] = 'R';
      }
      
      if ((cube[triple[0][0]][triple[0][1]] == cube[3][0] && cube[triple[1][0]][triple[1][1]] == cube[3][7])
          || (cube[triple[1][0]][triple[1][1]] == cube[3][0] && cube[triple[0][0]][triple[0][1]] == cube[3][7])) {
        mapping[cube[triple[2][0]][triple[2][1]]] = 'U';
      }
      if ((cube[triple[0][0]][triple[0][1]] == cube[3][0] && cube[triple[2][0]][triple[2][1]] == cube[3][7])
          || (cube[triple[2][0]][triple[2][1]] == cube[3][0] && cube[triple[0][0]][triple[0][1]] == cube[3][7])) {
        mapping[cube[triple[1][0]][triple[1][1]]] = 'U';
      }
      if ((cube[triple[1][0]][triple[1][1]] == cube[3][0] && cube[triple[2][0]][triple[2][1]] == cube[3][7])
          || (cube[triple[2][0]][triple[2][1]] == cube[3][0] && cube[triple[1][0]][triple[1][1]] == cube[3][7])) {
        mapping[cube[triple[0][0]][triple[0][1]]] = 'U';
      }
    }
    
    for (int i = 0; i < 6; i++) {
      for (int j = 0; j < 8; j++) {
        remap[i][j] = mapping[cube[i][j]];
      }
    }
    
    return remap;
  }
  
  static int[] orient = new int[7];
  static int[] perm = new int[6];
  static int[] assign = new int[7];
  
  static int deflate(char[][] cube) {
    for (int i = 0; i < 7; i++) {
      int[][] triple = locs[i];
      for (int j = 0; j < 3; j++) {
        String str = "" + cube[triple[j][0]][triple[j][1]]
                        + cube[triple[(j + 1) % 3][0]][triple[(j + 1) % 3][1]]
                        + cube[triple[(j + 2) % 3][0]][triple[(j + 2) % 3][1]];
        int k = 0;
        while (k < 7) {
          if (str.equals(cubes[k])) break;
          k++;
        }
        if (k < 7) {
          assign[k] = i;
          orient[k] = j;
        }
      }
    }
    
    if (printDebug) {
      System.out.println("DEFLATE");
      System.out.println(Arrays.toString(orient));
      System.out.println(Arrays.toString(assign));
    }
    
    
    return fastDeflate();
  }
  
  static int fastRotX(int index) {
    fastInflate(index);
    for (int i = 0; i < 7; i++) {
      if (assign[i] == 2 || assign[i] == 5 || assign[i] == 6) {
        orient[i] = (orient[i] + 1) % 3;
      }
      
      if (assign[i] == 1) assign[i] = 5;
      else if (assign[i] == 2) assign[i] = 1;
      else if (assign[i] == 5) assign[i] = 6;
      else if (assign[i] == 6) assign[i] = 2;
    }
    
    return fastDeflate();
  }
  
  static int fastRotY(int index) {
    fastInflate(index);
    for (int i = 0; i < 7; i++) {
      if (assign[i] == 3) assign[i] = 6;
      else if (assign[i] == 4) assign[i] = 3;
      else if (assign[i] == 5) assign[i] = 4;
      else if (assign[i] == 6) assign[i] = 5;
    }
    
    return fastDeflate();
  }
  
  static int fastRotZ(int index) {
    fastInflate(index);
    for (int i = 0; i < 7; i++) {
      if (assign[i] == 1 || assign[i] == 4 || assign[i] == 5) {
        orient[i] = (orient[i] + 1) % 3;
      }
      
      if (assign[i] == 0) assign[i] = 4;
      else if (assign[i] == 1) assign[i] = 0;
      else if (assign[i] == 4) assign[i] = 5;
      else if (assign[i] == 5) assign[i] = 1;
    }
    
    return fastDeflate();
  }
  
  static void fastInflate(int index) {
    for (int i = 0; i < 7; i++) {
      orient[6 - i] = index % 3;
      index /= 3;
    }
    
    for (int i = 0; i < 6; i++) {
      perm[i] = index % (i + 2);
      index /= i + 2;
    }
    
    assign[0] = 0;
    for (int i = 0; i < 6; i++) {
      for (int j = i; j >= perm[i]; j--) {
        assign[j + 1] = assign[j];
      }
      assign[perm[i]] = i + 1;
    }
  }
  
  static int fastDeflate() {
    int index = 0;
    
    for (int i = 6; i > 0; i--) {
      int j = 0;
      while (assign[j] != i) j++;
      perm[i - 1] = j;
      while (j < i) {
        assign[j] = assign[j + 1];
        j++;
      }
    }
    
    for (int i = 0; i < 6; i++) {
      index *= 7 - i;
      index += perm[5 - i];
    }
    
    for (int i = 0; i < 7; i++) {
      index *= 3;
      index += orient[i];
    }
    
    return index;
  }
  
  static char[][] inflate = new char[6][8];
  static char[][] inflate(int index) {
    fastInflate(index);
    
    if (printDebug) {
      System.out.println("INFLATE");
      System.out.println(Arrays.toString(orient));
      System.out.println(Arrays.toString(assign));
    }
    
    for (int i = 0; i < 7; i++) {
      String str = cubes[i];
      int[][] triple = locs[assign[i]];
      for (int j = 0; j < 3; j++) {
        inflate[triple[(orient[i] + j) % 3][0]][triple[(orient[i] + j) % 3][1]] = str.charAt(j);
      }
    }
    
    return inflate;
  }
  
  static {
    for (char[] c : inflate) Arrays.fill(c, '.');
    for (char[] c : rotX) Arrays.fill(c, '.');
    for (char[] c : rotY) Arrays.fill(c, '.');
    for (char[] c : rotZ) Arrays.fill(c, '.');
  }
  
  static int base = deflate(new char[][] {"..UU....".toCharArray(),
      "..UU....".toCharArray(),
      "LLFFRRBB".toCharArray(),
      "LLFFRRBB".toCharArray(),
      "..DD....".toCharArray(),
      "..DD....".toCharArray()});
}
