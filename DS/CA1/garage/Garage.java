package garage;
import java.util.ArrayList;
import garage.cars.*;

public class Garage {

  public void newCar(ArrayList<String> moduleList) {
    String model = moduleList.get(0);
    String manufacturer = moduleList.get(1);
    int productionYear = Integer.parseInt( moduleList.get(2) );
    float traveledDistance = Float.parseFloat( moduleList.get(3) );
    String classModel = moduleList.get(4);
    float basePrice = Float.parseFloat( moduleList.get(5) );
    boolean crashed = moduleList.get(6).equals("crashed")? true : false;
    String color = moduleList.get(7);

    if( classModel.equals("A") )
      cars.add( new CarA(model, manufacturer, productionYear, traveledDistance, basePrice, crashed, color) );
    else if( classModel.equals("B") )
      cars.add( new CarB(model, manufacturer, productionYear, traveledDistance, basePrice, crashed, color) );
    else
      cars.add( new CarC(model, manufacturer, productionYear, traveledDistance, basePrice, crashed, color) );
  }

  public boolean removeCar(ArrayList<String> moduleList) {
    String model = moduleList.get(0);
    String manufacturer = moduleList.get(1);
    int productionYear = Integer.parseInt( moduleList.get(2) );
    float traveledDistance = Float.parseFloat( moduleList.get(3) );
    String classModel = moduleList.get(4);
    float basePrice = Float.parseFloat( moduleList.get(5) );
    boolean crashed = moduleList.get(6).equals("crashed")? true : false;
    String color = moduleList.get(7);

    // search on carsList!
    for (int i = 0; i<cars.size(); i++)
      if( cars.get(i).getModel().equals(model) &&
          cars.get(i).getManufacturer().equals(manufacturer) &&
          cars.get(i).getClassModel().equals(classModel) &&
          cars.get(i).getColor().equals(color) &&
          cars.get(i).getProductionYear() == productionYear &&
          cars.get(i).getTraveledDistance() == traveledDistance &&
          cars.get(i).getBasePrice() == basePrice &&
          cars.get(i).isCrashed() == crashed) {
            cars.remove(i);
            return true;
          }

    return false;
  }

  // find cars by modelName and manufacturer
  public ArrayList<Car> findCars(String modelName, String manufacturerName) {
    ArrayList<Car> carList = new ArrayList<>();
    for(Car car : cars)
      if( car.getModel().equals(modelName) && car.getManufacturer().equals(manufacturerName) )
        carList.add(car);
    return carList;
  }

  public ArrayList<Float> getSellPrices(String modelName, String manufacturerName) {
    ArrayList<Float> priceList = new ArrayList<>();
    ArrayList<Car> carList = findCars(modelName, manufacturerName);
    for(Car car : carList)
      priceList.add( car.getSellPrice() );
    return priceList;
  }

  public ArrayList<Float> getRentPrices(String modelName, String manufacturerName) {
    ArrayList<Float> priceList = new ArrayList<>();
    ArrayList<Car> carList = findCars(modelName, manufacturerName);
    for(Car car : carList)
      priceList.add( car.getRentPrice() );
    return priceList;
  }

  public void export() {
    for(Car car : cars)
      System.out.println(car.getModel() + " " + car.getManufacturer());
  }


  private ArrayList<Car> cars = new ArrayList<>();
}
