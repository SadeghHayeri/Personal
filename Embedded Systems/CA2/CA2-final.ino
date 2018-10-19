#include <Wire.h>
#include <Adafruit_Sensor.h>
#include <Adafruit_ADXL345_U.h>

#include <ESP8266WiFi.h>
#include <ESP8266WebServer.h>

const char* ssid = "NODE-MCU-W";
const char* password = "12345678";

const int trigPin = D5;
const int echoPin = D6;

const int led = 13;

/* Assign a unique ID to this sensor at the same time */
Adafruit_ADXL345_Unified accel = Adafruit_ADXL345_Unified(12345);

const float deltaX = 0.47;
const float deltaY = 0;
const float deltaZ = 2.16;

long long int lastTime = 0;
float accDistance = 0;
float ultraStartDist = 0;

ESP8266WebServer server(80);
void handleRoot() {
  digitalWrite(led, 1);
  server.send(200, "text/plain", "hello from esp8266!");
  digitalWrite(led, 0);
}

void handleNotFound(){
  digitalWrite(led, 1);
  String message = "File Not Found\n\n";
  message += "URI: ";
  message += server.uri();
  message += "\nMethod: ";
  message += (server.method() == HTTP_GET)?"GET":"POST";
  message += "\nArguments: ";
  message += server.args();
  message += "\n";
  for (uint8_t i=0; i<server.args(); i++){
    message += " " + server.argName(i) + ": " + server.arg(i) + "\n";
  }
  server.send(404, "text/plain", message);
  digitalWrite(led, 0);
}

void displaySensorDetails(void)
{
  sensor_t sensor;
  accel.getSensor(&sensor);
  Serial.println("------------------------------------");
  Serial.print  ("Sensor:       "); Serial.println(sensor.name);
  Serial.print  ("Driver Ver:   "); Serial.println(sensor.version);
  Serial.print  ("Unique ID:    "); Serial.println(sensor.sensor_id);
  Serial.print  ("Max Value:    "); Serial.print(sensor.max_value); Serial.println(" m/s^2");
  Serial.print  ("Min Value:    "); Serial.print(sensor.min_value); Serial.println(" m/s^2");
  Serial.print  ("Resolution:   "); Serial.print(sensor.resolution); Serial.println(" m/s^2");
  Serial.println("------------------------------------");
  Serial.println("");
  delay(500);
}

void displayDataRate(void)
{
  Serial.print  ("Data Rate:    ");

  switch(accel.getDataRate())
  {
    case ADXL345_DATARATE_3200_HZ:
      Serial.print  ("3200 ");
      break;
    case ADXL345_DATARATE_1600_HZ:
      Serial.print  ("1600 ");
      break;
    case ADXL345_DATARATE_800_HZ:
      Serial.print  ("800 ");
      break;
    case ADXL345_DATARATE_400_HZ:
      Serial.print  ("400 ");
      break;
    case ADXL345_DATARATE_200_HZ:
      Serial.print  ("200 ");
      break;
    case ADXL345_DATARATE_100_HZ:
      Serial.print  ("100 ");
      break;
    case ADXL345_DATARATE_50_HZ:
      Serial.print  ("50 ");
      break;
    case ADXL345_DATARATE_25_HZ:
      Serial.print  ("25 ");
      break;
    case ADXL345_DATARATE_12_5_HZ:
      Serial.print  ("12.5 ");
      break;
    case ADXL345_DATARATE_6_25HZ:
      Serial.print  ("6.25 ");
      break;
    case ADXL345_DATARATE_3_13_HZ:
      Serial.print  ("3.13 ");
      break;
    case ADXL345_DATARATE_1_56_HZ:
      Serial.print  ("1.56 ");
      break;
    case ADXL345_DATARATE_0_78_HZ:
      Serial.print  ("0.78 ");
      break;
    case ADXL345_DATARATE_0_39_HZ:
      Serial.print  ("0.39 ");
      break;
    case ADXL345_DATARATE_0_20_HZ:
      Serial.print  ("0.20 ");
      break;
    case ADXL345_DATARATE_0_10_HZ:
      Serial.print  ("0.10 ");
      break;
    default:
      Serial.print  ("???? ");
      break;
  }
  Serial.println(" Hz");
}

void displayRange(void)
{
  Serial.print  ("Range:         +/- ");

  switch(accel.getRange())
  {
    case ADXL345_RANGE_16_G:
      Serial.print  ("16 ");
      break;
    case ADXL345_RANGE_8_G:
      Serial.print  ("8 ");
      break;
    case ADXL345_RANGE_4_G:
      Serial.print  ("4 ");
      break;
    case ADXL345_RANGE_2_G:
      Serial.print  ("2 ");
      break;
    default:
      Serial.print  ("?? ");
      break;
  }
  Serial.println(" g");
}


void initUltraSonic() {
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
}

int readDistanceUltraSonic() {
  long duration;
  int distance;

  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);

  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);

  duration = pulseIn(echoPin, HIGH);
  distance = duration*0.034/2;

  return distance;
}

void initWebServer() {
  WiFi.softAP(ssid);

  Serial.begin(9600);
  Serial.println("Accelerometer Test"); Serial.println("");

  IPAddress myIP = WiFi.softAPIP();
  Serial.print("AP IP address: ");
  Serial.println(myIP);

  // Start the server
  server.begin();
  Serial.println("Server started");

  server.begin();
  Serial.println("HTTP server started");
}

void initAccel() {
  /* Initialise the sensor */
  if(!accel.begin())
  {
    /* There was a problem detecting the ADXL345 ... check your connections */
    Serial.println("Ooops, no ADXL345 detected ... Check your wiring!");
    while(1);
  }

  /* Set the range to whatever is appropriate for your project */
  accel.setRange(ADXL345_RANGE_16_G);
  // displaySetRange(ADXL345_RANGE_8_G);
  // displaySetRange(ADXL345_RANGE_4_G);
  // displaySetRange(ADXL345_RANGE_2_G);

  /* Display some basic information on this sensor */
  displaySensorDetails();

  /* Display additional settings (outside the scope of sensor_t) */
  displayDataRate();
  displayRange();
  Serial.println("");

}

void startHandle() {
  server.send(200, "text/plain", "started!");
  ultraStartDist = readDistanceUltraSonic();
  accDistance = 0;
}

void endHandle() {
  float ultraDistNow = readDistanceUltraSonic();
  float ultraDist = ultraDistNow - ultraStartDist;

  String response;
  response += "ultra(diff): " + String(ultraDist);
  response += "\n - ";
  response += "ultra(now): " + String(ultraDistNow);
  response += "\n - ";
  response += "ultra(befor): " + String(ultraStartDist);
  response += "\n - ";
  response += "acc: " + String(accDistance * 100);
  server.send(200, "text/plain", response);

  ultraStartDist = ultraDistNow;
  accDistance = 0;
}

void setup(void)
{
  initWebServer();
  initAccel();
  initUltraSonic();
  lastTime = millis();

  server.on("/start", startHandle);
  server.on("/end", endHandle);
  server.onNotFound(handleNotFound);
}

void loop(void)
{
  server.handleClient();

  /* Get a new sensor event */
  sensors_event_t event;
  accel.getEvent(&event);

  float x = event.acceleration.x - deltaX;
  float y = event.acceleration.y - deltaY;
  float z = event.acceleration.z - deltaZ;

  float a = sqrt(x*x + y*y);

  /* Display the results (acceleration is measured in m/s^2) */
  Serial.print("X: "); Serial.print(x); Serial.print("  ");
  Serial.print("Y: "); Serial.print(y); Serial.print("  ");
  Serial.print("Z: "); Serial.print(z); Serial.print("  ");Serial.print("m/s^2 ");

  long long currentTime = millis();
  accDistance += 0.5 * a * pow(currentTime-lastTime, 2) / 1e6;
  lastTime = currentTime;

  Serial.print("Acceleration Distance: "); Serial.print(accDistance * 100); Serial.print("  ");Serial.println("cm");
  //Serial.print("Ultrasonic Distance: "); Serial.print(readDistanceUltraSonic()); Serial.println("cm ");
  delay(200);
}
