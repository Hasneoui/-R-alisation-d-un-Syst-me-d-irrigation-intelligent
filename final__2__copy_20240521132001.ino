


#define SENSOR_READ_DELAY 500
#define FULL_MOISTURE_READING 290
#define NO_MOISTURE_READING 1023
#define CUT_OFF_MOISTURE_PERCENTAGE 50
#define PUMP1_WATERING_TIME 2000



#include <DHT.h>
#include <DHT_U.h>
#include <SoftwareSerial.h>
#define PinCapteur 4   // Pin digital auquel on relie le capteur
#define Type DHT11 // Type de capteur
#define Float_Switch 3
DHT dht(PinCapteur, Type);




int inputSensorPin1=A0; 
int pumpPin1=2;
int LED = 8;





char inchar; // Will hold the incoming 
SoftwareSerial blue(0, 1); 
String TextForSms ;
String humidity = " Humidity: %";
String temperature = "   Temperature";
String sign = " *C";



void setup() {
  Serial.begin(9600);
   dht.begin();
    blue.begin(9600);
  pinMode(pumpPin1,OUTPUT);

  digitalWrite(pumpPin1,HIGH);
  pinMode(LED, OUTPUT);

 
  pinMode(Float_Switch, INPUT_PULLUP);



     
 

  

}
void getMoisturePercentageAndWaterIt(int sensorValue , int outPinNo , int wateringTime)
{
  sensorValue = constrain (sensorValue , FULL_MOISTURE_READING , NO_MOISTURE_READING);
  int moisturePercentage= map(sensorValue , FULL_MOISTURE_READING ,NO_MOISTURE_READING,100 ,0);

  if (moisturePercentage< CUT_OFF_MOISTURE_PERCENTAGE)
  {
    digitalWrite ( outPinNo , LOW);
    delay(wateringTime);
    digitalWrite (outPinNo , HIGH);
    

   
  } 
}




void loop() {



  if(digitalRead(Float_Switch) == HIGH)
  {
    digitalWrite(LED, HIGH); //Turn LED on
  }

 else
  {
    digitalWrite(LED, LOW); //Turn LED off
  }



  int inputSensorPin1Value=analogRead(inputSensorPin1);
 
getMoisturePercentageAndWaterIt(inputSensorPin1Value,pumpPin1,PUMP1_WATERING_TIME);
delay (SENSOR_READ_DELAY);





if(blue.available() == 0);
 if(blue.available() >0)
  {
 
    inchar=blue.read(); 
  Serial.println(inchar);
    delay(20);
    if (inchar=='v')
    {
      delay(10);
 
   Serial.println(inchar);
    
  
  delay(2000);
 
 
  int h = dht.readHumidity();
  // Read temperature as Celsius
  int t = dht.readTemperature();
  // Read temperature as Fahrenheit
  int f = dht.readTemperature(true);
  int HUMIDITY = analogRead(A0);
  Serial.println (HUMIDITY);
  
  
  if (isnan(h) || isnan(t) || isnan(f)) {
    Serial.println("Failed to read from DHT sensor!");
    return;
}
 

  int hi = dht.computeHeatIndex(f, h);
 

  
  TextForSms = TextForSms + "HUMIDITY: ";
  TextForSms.concat(h);
  TextForSms = TextForSms + "%    TEMPERATURE: ";
  TextForSms.concat(t);
  TextForSms = TextForSms + "*C";
   blue.print(TextForSms);
  Serial.println(TextForSms);
  delay(2000);
 TextForSms = " ";
    }
 
}


 

  
  
  }
