package garage.cars;
import java.util.Calendar;

public class CarA extends Car {


  public CarA(String model, String manufacturer, int productionYear,
   float traveledDistance, float basePrice,
   boolean crashed, String color) {
     super(model, manufacturer, productionYear, traveledDistance, basePrice, crashed, color);
   }


   public float getSellPrice() {
     int yearPenalty = (int)Calendar.getInstance().get(Calendar.YEAR) - this.productionYear;
     yearPenalty = (yearPenalty > 20) ? 20 : yearPenalty;  // maximum to 20%

     int distancPenalty = (int)this.traveledDistance / 50;
     distancPenalty = (distancPenalty > 30) ? 30 : distancPenalty; // maximum to 30%

     return this.basePrice - (this.basePrice*yearPenalty/100) - (this.basePrice*distancPenalty/100);
   }

   public float getRentPrice() {
     return -1;
   }

   public String getClassModel() {
     return "A";
   }

}
