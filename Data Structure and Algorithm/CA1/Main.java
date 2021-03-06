import util.Csv;
import util.Collections;
import garage.Garage;

import java.io.BufferedReader;
import java.io.FileReader;
import java.io.IOException;
import java.io.InputStreamReader;

import java.util.ArrayList;

public class Main {

  private static final String CARSFILES = "cars.csv";

  public static void main(String[] args) {
    Garage garage = new Garage();
    readCarsFile(garage);
    getInput(garage);
  }

  public static void readCarsFile(Garage garage) {
		try (BufferedReader br = new BufferedReader(new FileReader(CARSFILES))) {

			String sCurrentLine;
			while ((sCurrentLine = br.readLine()) != null)
        garage.newCar(Csv.parse(sCurrentLine, ","));

		} catch (IOException e) {
			e.printStackTrace();
		}
	}

  public static void printPrices(ArrayList<Float> prices) {
    if(prices.size() != 0) {

      ArrayList<Float> sortedPrices = Collections.mergeSort(prices);
      for(float f : sortedPrices)
        if( f != -1000 )
          System.out.printf("%.2f\n", f);
        else {
          System.out.println("NoRent");
          break;
        }

    } else {
      System.out.println("NotFound");
    }
  }

  public static void getInput(Garage garage) {

    BufferedReader br = null;
    try {
        br = new BufferedReader(new InputStreamReader(System.in));

        String input;
        while ( (input = br.readLine()) != null ) {

          ArrayList<String> list = Csv.parse(input, " ");

          switch (list.get(0)) {
            case "add":
              list.remove(0); //remove 'add' command!
              garage.newCar(list);
              break;
            case "rmv":
              list.remove(0); //remove 'rmv' command!
              if(!garage.removeCar(list))
                System.out.println("NotFound");
              break;
            case "sellprice":
              printPrices( garage.getSellPrices(list.get(1), list.get(2)) );
              break;
            case "rentprice":
              printPrices( garage.getRentPrices(list.get(1), list.get(2)) );
              break;
            case "export":
              garage.export();
              break;
            case "quit":
              return;
          }
        }
    } catch (IOException e) {
        e.printStackTrace();
    } finally {
        if (br != null) {
            try {
                br.close();
            } catch (IOException e) {
                e.printStackTrace();
            }
        }
    }

  }


}
