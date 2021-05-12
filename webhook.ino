// This #include statement was automatically added by the Particle IDE.
#include <ThingSpeak.h>

// This #include statement was automatically added by the Particle IDE.
//#include "TinyDHT.h"

#include "TinyDHT.h"
//#include "ThingSpeak.h"

#define DHTPIN D6  // DHT connected to Arduino Uno Digital Pin 2
#define DHTTYPE DHT11   // DHT 11 



DHT dht(DHTPIN, DHTTYPE);

TCPClient client;
//DNSClient client;

unsigned long myChannelNumber = 1385783;
const char * myWriteAPIKey = "V5DBNHTTO3P6FST9";


void setup() {
  ThingSpeak.begin(client);
  Serial.begin(9600); // Output status on Uno serial monitor
  Serial.println("DHTxx test!");
  Particle.subscribe("hook-response/temperatureproject", myHandler, MY_DEVICES);
  //Particle.subscribe("IOTTest", l, ALL_DEVICES);
 
  dht.begin();
}

void loop() {
  // Reading temperature or humidity takes about 250 milliseconds!
  // Sensor readings may also be up to 2 seconds 'old' (its a very slow sensor)
  int8_t h = dht.readHumidity();
  int16_t t = dht.readTemperature(1);
  //t = (t-32)*5/9;
  int16_t t1 = dht.readTemperature(0);
  
  
  
    Particle.publish("temperatureproject", String (t1), PUBLIC);


    //Particle.publish("Tempereture", String (t), PUBLIC);
    //Particle.publish("Humidity", String (h), PUBLIC);

  ThingSpeak.setField(1,t);
  ThingSpeak.setField(2,h);

  // check if returns are valid then something went wrong!
  if ( t == BAD_TEMP || h == BAD_HUM ) { // if error conditions          
    Serial.println("Failed to read from DHT");
  } else {
    Serial.print("Humidity: "); 
    Serial.print(h);
    Serial.print(" %\t");
    Serial.print("Temperature: "); 
    Serial.print(t);
    Serial.print("secondTemperature1: "); 
    Serial.print(t1);
    Serial.println(" *C");
  }

  ThingSpeak.writeFields(myChannelNumber, myWriteAPIKey);
  delay(30000);
}

void myHandler(const char *event, const char *data) {
  // Handle the integration response
}
