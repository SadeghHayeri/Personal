import java.util.*;
import java.math.*;
import java.io.*;

class Dallas{

  static class FastReader
    {
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

  public static int par(int index) {
    return (index+1)/2-1;
  }

  public static int findLevel(int index) {
    return log(index+1, 2);
  }

  public static int log(int x, int base)
  {
      return (int) (Math.log(x) / Math.log(base));
  }

  public static int findDistance(ArrayList<Integer> list, int num1, int num2) {
    num1 = list.indexOf( num1 );
    num2 = list.indexOf( num2 );

    if( num1 < num2 ) {
      int tmp = num1;
      num1 = num2;
      num2 = tmp;
    }

    int diff = findLevel(num1) - findLevel(num2);

    for(int i = 0; i<diff; i++)
      num1 = par(num1);

    while( true ) {
      if( num1 == num2 )
        return diff;

      num1 = par(num1);
      num2 = par(num2);
      diff += 2;

    }

  }

  public static void main(String args[]){
    PriorityQueue<Integer> heap = new PriorityQueue<>();

    FastReader scan = new FastReader();
    int n = scan.nextInt();
    int q = scan.nextInt();

    for (int i = 0; i<n; i++) {
      int num = scan.nextInt();
      heap.add(num);
    }

    ArrayList<Integer> list = new ArrayList<Integer>( heap );

    for (int i = 0; i<q; i++) {
      int a = scan.nextInt();
      int b = scan.nextInt();
      System.out.println( findDistance( list, a, b) );
    }

  }

}
