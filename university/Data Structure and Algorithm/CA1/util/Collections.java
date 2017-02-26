package util;
import java.util.ArrayList;

public class Collections {

  private static ArrayList<Float> merge(ArrayList<Float> left, ArrayList<Float> right) {
    int arraySize = left.size() + right.size();
    ArrayList<Float> list = new ArrayList<>();

    int i = 0, j = 0;
    for (int k = 0; k < arraySize; k++)
      if( i >= left.size() || (j<right.size() && left.get(i)>right.get(j)) ) {
        list.add( right.get(j++) );
      } else {
        list.add( left.get(i++) );
      }

    return list;
  }

  public static ArrayList<Float> mergeSort(ArrayList<Float> list) {

    int n = list.size();
    if(n < 2)
      return list;

    int mid = n/2;
    ArrayList<Float> left = new ArrayList<>();
    ArrayList<Float> right = new ArrayList<>();

    // fill left & right arrays
    for (int i = 0; i<mid; i++)
      left.add( list.get(i) );
    for (int i = mid; i<list.size(); i++)
      right.add( list.get(i) );

    // sort arrays
    left = mergeSort(left);
    right = mergeSort(right);

    return merge(left, right);
  }

}
