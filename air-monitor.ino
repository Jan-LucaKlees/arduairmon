//Libraries
#include <DHT.h>
#include <MPX4115A.h>
#include <ArduinoJson.h>

// DHT 1 setup
#define DHT1PIN 3
#define DHT1TYPE DHT22
DHT dht1(DHT1PIN, DHT1TYPE);

// DHT 2 setup
#define DHT2PIN 2
#define DHT2TYPE DHT22
DHT dht2(DHT2PIN, DHT2TYPE);

// MPX4115A Pressure sensor setup
#define MPX4115A_PIN 0
const double VCC_CORRECTION = 4.95/4.918777;  // Measured Vcc by multimeter divided by reported Vcc
MPX4115A mpx4115a(MPX4115A_PIN, VCC_CORRECTION);

//Variables
float humidity;
float temperature;
float pressure;

void setup() {
    Serial.begin(9600);
    dht1.begin();
    dht2.begin();
}

void loop(){
    // initialize Json Object
    StaticJsonBuffer<400> jsonBuffer;
    JsonObject& json = jsonBuffer.createObject();
    json["millis"] = millis();

    // create array for sensors
    JsonArray& sensorJson = json.createNestedArray("sensors");

    // humidity 1
    JsonObject& hum1Json = sensorJson.createNestedObject();
    hum1Json["id"] = "rel_hum1_1";
    hum1Json["label"] = "Relative Humidity";
    hum1Json["value"] = dht1.readHumidity();
    hum1Json["unit"] = "%";

    // humidity 2
    JsonObject& hum2Json = sensorJson.createNestedObject();
    hum2Json["id"] = "rel_hum1_2";
    hum2Json["label"] = "Relative Humidity";
    hum2Json["value"] = dht2.readHumidity();
    hum2Json["unit"] = "%";

    // temperature 1
    JsonObject& temp1Json = sensorJson.createNestedObject();
    temp1Json["id"] = "temp_1";
    temp1Json["label"] = "Temprature";
    temp1Json["value"] = dht1.readTemperature();
    temp1Json["unit"] = "C";

     // temperature 2
    JsonObject& temp2Json = sensorJson.createNestedObject();
    temp2Json["id"] = "temp_2";
    temp2Json["label"] = "Temprature";
    temp2Json["value"] = dht2.readTemperature();
    temp2Json["unit"] = "C";

    // pressure
    JsonObject& pressureJson = sensorJson.createNestedObject();
    pressureJson["id"] = "air_pressure";
    pressureJson["label"] = "Barometric Air Pressure";
    pressureJson["value"] = mpx4115a.readKPa();
    pressureJson["unit"] = "kPa";

    // Vcc
    JsonObject& vccJson = sensorJson.createNestedObject();
    vccJson["id"] = "vcc";
    vccJson["label"] = "Vcc";
    vccJson["value"] = mpx4115a.readVcc();
    vccJson["unit"] = "V";

    // Vout from MPX4115A pressure sensor
    //JsonObject& voutJson = sensorJson.createNestedObject();
    //voutJson["id"] = "vout";
    //voutJson["value"] = mpx4115a.readVout();
    //voutJson["unit"] = "V";

    json.printTo(Serial);

    Serial.println();
    
    delay(10000);
}
