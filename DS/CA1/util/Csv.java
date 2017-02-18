package util;
import java.util.ArrayList;

public class Csv {

  public static ArrayList<String> parse( String line, String separator ) {
    String lineList[] = line.split(separator);
    ArrayList<String> result = new ArrayList<>();
    for( String element : lineList )
      result.add( element.trim() );
    return result;
  }

}
