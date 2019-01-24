//Libraries
#include <DHT.h>
#include <MPX4115A.h>
#include <ArduinoJson.h>

// DHT setup
#define DHT1PIN 2
#define DHT1TYPE DHT22
DHT dht(DHT1PIN, DHT1TYPE);

// MPX4115A Pressure sensor setup
// #define MPX4115A_PIN 0
// const double VCC_CORRECTION = 5.12/5.0;  // Measured Vcc by multimeter divided by reported Vcc
// MPX4115A mpx4115a(MPX4115A_PIN, VCC_CORRECTION);

//Variables
float humidity;
float temperature;
// float pressure;

void setup() {
    Serial.begin(9600);
    dht.begin();
}

void loop(){
    // initialize Json Object
    StaticJsonBuffer<400> jsonBuffer;
    JsonObject& json = jsonBuffer.createObject();
    json["millis"] = millis();

    // create array for sensors
    JsonObject& sensorJson = json.createNestedObject("sensors");

    // humidity
    JsonObject& humJson = sensorJson.createNestedObject("rel_hum");
    humJson["label"] = "Relative Humidity";
    humJson["value"] = dht.readHumidity();
    humJson["unit"] = "%";

    // temperature
    JsonObject& tempJson = sensorJson.createNestedObject("temp");
    tempJson["label"] = "Temprature";
    tempJson["value"] = dht.readTemperature();
    tempJson["unit"] = "C";
    
    // pressure
    // JsonObject& pressureJson = sensorJson.createNestedObject("air_pressure");
    // pressureJson["label"] = "Barometric Air Pressure";
    // pressureJson["value"] = mpx4115a.readKPa();
    // pressureJson["unit"] = "kPa";

    // Vout from MPX4115A pressure sensor
    // JsonObject& voutJson = sensorJson.createNestedObject("air_pressure_raw");
    // voutJson["id"] = "Raw MPX4115A output readout";
    // voutJson["value"] = mpx4115a.readVout();
    // voutJson["unit"] = "V";

    // CO2
    // JsonObject& co2Json = sensorJson.createNestedObject("co2");
    // co2Json["label"] = "CO2 Level raw";
    // co2Json["value"] =  analogRead( 1 ) / 1023.0;
    // co2Json["unit"] = "ppm";

    // Vcc
    // JsonObject& vccJson = sensorJson.createNestedObject("vcc");
    // vccJson["label"] = "Vcc";
    // vccJson["value"] = mpx4115a.readVcc();
    // vccJson["unit"] = "V";

    json.printTo(Serial);

    Serial.println();
    
    delay(10000);
}
