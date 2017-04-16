import java.util.*;
import java.math.*;
import java.io.*;

class main{

  public class Pair<L,R> {

    private final L left;
    private final R right;

    public Pair(L left, R right) {
    this.left = left;
    this.right = right;
    }

    public L getLeft() { return left; }
    public R getRight() { return right; }

    @Override
    public int hashCode() { return left.hashCode() ^ right.hashCode(); }

    @Override
    public boolean equals(Object o) {
    if (!(o instanceof Pair)) return false;
    Pair pairo = (Pair) o;
    return this.left.equals(pairo.getLeft()) &&
           this.right.equals(pairo.getRight());
    }

  }

  static class FastReader {
      BufferedReader br;
      StringTokenizer st;

      public FastReader()
      {
          br = new BufferedReader(new
                   InputStreamReader(System.in));
      }

      String next()
      {
          while (st == null || !st.hasMoreElements())
          {
              try
              {
                  st = new StringTokenizer(br.readLine());
              }
              catch (IOException  e)
              {
                  e.printStackTrace();
              }
          }
          return st.nextToken();
      }

      int nextInt()
      {
          return Integer.parseInt(next());
      }

      String nextLine()
      {
          String str = "";
          try
          {
              str = br.readLine();
          }
          catch (IOException e)
          {
              e.printStackTrace();
          }
          return str;
      }
  }

  public static void main(String args[]){
    ArrayList< Queue<Integer> > arr1 = new ArrayList<>();
    ArrayList< Queue<Integer> > arr2 = new ArrayList<>();

    for (int i = 0; i<30; i++)
      arr1.add( new ArrayList<Integer>() );
      arr1.add( new ArrayList<Integer>() );


    // FastReader scan = new FastReader();
    // int n = scan.nextInt();
    // int sec = 0;
    //
    // for (int i = 0; i<n; i++) {
    //   String k = scan.next();
    //   int a = scan.nextInt();
    //   int b = scan.nextInt();
    //
    //   if( k.equals("+") ) {
    //     l = ArrayList<Integer>
    //     arr.get( b+1 ).add(  );
    //   }
    //
    //   sec++;
    // }

  }
}
