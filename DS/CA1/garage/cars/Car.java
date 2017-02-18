package garage.cars;

public abstract class Car {

  public Car(String model, String manufacturer, int productionYear,
   float traveledDistance, float basePrice,
   boolean crashed, String color) {

     this.model = model;
     this.manufacturer = manufacturer;
     this.productionYear = productionYear;
     this.traveledDistance = traveledDistance;
     this.basePrice = basePrice;
     this.crashed = crashed;
     this.color = color;

  }

  public abstract float getSellPrice();
  public abstract float getRentPrice();

  public float getTraveledDistance() { return traveledDistance; }
  public int getProductionYear() { return productionYear; }
  public String getManufacturer() { return manufacturer; }
  public float getBasePrice() { return basePrice; }
  public boolean isCrashed() { return crashed; }
  public String getModel() { return model; }
  public String getColor() { return color; }
  public abstract String getClassModel();

  protected String model;
  protected String manufacturer;
  protected int productionYear;
  protected float traveledDistance;
  protected float basePrice;
  protected boolean crashed;
  protected String color;

}
