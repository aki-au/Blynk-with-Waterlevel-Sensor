/* Change these values based on your calibration values */
#define BLYNK_PRINT Serial
#include <ESP8266WiFi.h>
#in
int FloatSensor = D3; //D4 pin of NodeMCU

char auth[] = "your code";

// Your WiFi credentials.
// Set password to "" for open networks.
char ssid[] = "Name";
char pass[] = "Pwd";
WidgetLED redLED(V2); //register to virtual pin 2
WidgetLED onLED(V3); //register to virtual pin 3
WidgetLED greenLED(V4); //register to virtual pin 4
BlynkTimer timer;
WidgetLCD lcd(V1);
int lowerThreshold = 300;
int upperThreshold = 600;

// Sensor pins
#define sensorPower D7
#define sensorPin A0

// Value for storing water level
int val = 0;


void pushlevel()
{  int level = readSensor();

  if (level == 0) {
    Serial.println("Water Level: Empty");
    Blynk.virtualWrite(V0,level); 

    lcd.print(4, 0, "Empty");
    Serial.println(level);
    redLED.off();
    onLED.off();
    greenLED.off();    
  }
  else if (level > 0 && level <= lowerThreshold) {
    Serial.println("Water Level: Low");
    Blynk.virtualWrite(V0,level); 

    lcd.print(4, 0, "Low");
    Serial.println(level);
    redLED.on();
    onLED.off();
    greenLED.off();    
  
  }
  else if (level > lowerThreshold && level <= upperThreshold) {
    Serial.println("Water Level: Medium");
    Blynk.virtualWrite(V0,level); 

    lcd.print(4, 0, "Medium");
    Serial.println(level);
    redLED.off();
    onLED.on();
    greenLED.off();    
  }
  
  else if (level > upperThreshold) {
    Serial.println("Water Level: High");
    Blynk.virtualWrite(V0,level); 

    lcd.print(4, 0, "High");
    Serial.println(level);
    redLED.off();
    onLED.off();
    greenLED.on();    
  }
  }

void setup() {
  Serial.begin(9600);
  pinMode(sensorPower, OUTPUT);
  digitalWrite(sensorPower, LOW);
  Blynk.begin(auth, ssid, pass);
  Blynk.virtualWrite(V0,0);
  greenLED.off();
  redLED.off();
  onLED.off();
  lcd.clear();
  timer.setInterval(1000L, pushlevel);
  // You can also specify server:
  //Blynk.begin(auth, ssid, pass, "blynk-cloud.com", 80);
  //Blynk.begin(auth, ssid, pass, IPAddress(192,168,1,100), 8080);
}

void loop()
{
  Blynk.run();
  timer.run();
}

//This is a function used to get the reading
int readSensor() {
  digitalWrite(sensorPower, HIGH);
  delay(10);
  val = analogRead(sensorPin);
  digitalWrite(sensorPower, LOW);
  return val;
}
