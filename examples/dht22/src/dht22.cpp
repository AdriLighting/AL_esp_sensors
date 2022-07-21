#include <AL_sensors.h>

Sensor<dht22Class>  _dht22;
// uint32_t            _timer_sensorMesure = 0;

void setup()
{
  Serial.begin(115200);

  for(unsigned long const serialBeginTime = millis(); !Serial && (millis() - serialBeginTime > 5000); ) { }
  delay(1000);

  Serial.println();
  Serial.println("STARTUP");

  _dht22.create(D7);

}

void loop() {
  // if ( (millis() - _timer_sensorMesure) > 3000 ) {
  //   _timer_sensorMesure = millis();
  // }
  if ( _dht22.temperature_loop("c") ) {
    DynamicJsonDocument doc(1024);
    JsonObject obj = doc.createNestedObject(F("dht22"));
    _dht22.get_json(obj);
    serializeJsonPretty(doc, Serial);Serial.println();  
    delay(2);     
  } 
}