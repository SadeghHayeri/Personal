package garage.cars;
public class CarC extends Car {

  private static final float baseRentPrice = 0.15f;
  private static final float rentPercent = 0.2f;

  public CarC(String model, String manufacturer, int productionYear,
   float traveledDistance, float basePrice,
   boolean crashed, String color) {
     super(model, manufacturer, productionYear, traveledDistance, basePrice, crashed, color);
   }

   public float getSellPrice() {
     int crashPenalty = this.crashed ? (15) : 0;
     int colorPenalty = this.color.equals("white") ? 5 : 0;
     int colorbonus = (this.color.equals("red") || this.color.equals("silver")) ? 5 : 0;

     int distancPenalty = ((int)this.traveledDistance / 50) * 2;
     distancPenalty = (distancPenalty > 40) ? 40 : distancPenalty; // maximum to 40%

     return this.basePrice - (this.basePrice*distancPenalty/100) - (this.basePrice*crashPenalty/100) - (this.basePrice*colorPenalty/100) + (this.basePrice*colorbonus/100);
   }

   public float getRentPrice() {
     return baseRentPrice + (this.basePrice*rentPercent/100);
   }

   public String getClassModel() {
     return "C";
   }


 }
