package garage.cars;

public class CarB extends Car {

  private static final float baseRentPrice = 0.3f;
  private static final float rentPercent = 0.1f;

  public CarB(String model, String manufacturer, int productionYear,
   float traveledDistance, float basePrice,
   boolean crashed, String color) {
     super(model, manufacturer, productionYear, traveledDistance, basePrice, crashed, color);
   }

   public float getSellPrice() {
     int crashPenalty = this.crashed ? (30) : 0;
     int colorbonus = (this.color.equals("white") || this.color.equals("black")) ? 5 : 0;

     return this.basePrice - (this.basePrice*crashPenalty/100) + (this.basePrice*colorbonus/100);
   }

   public float getRentPrice() {
     return baseRentPrice + (this.basePrice*rentPercent/100);
   }

   public String getClassModel() {
     return "B";
   }

}
