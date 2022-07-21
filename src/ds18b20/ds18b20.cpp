#include "ds18b20.h"


DS18B20Class::DS18B20Class(uint8_t pin) {
  _whire  = new OneWire(pin);
  _module = new DallasTemperature(_whire);
  begin();
  _module->setResolution(9);
  _pin = pin;
}
void DS18B20Class::begin(){
  _module->begin(); 
}
uint8_t DS18B20Class::get_pin() {return _pin;}
void DS18B20Class::read_temperature(float & result, boolean & isNan){
  _module->requestTemperatures(); 
  float temp = _module->getTempCByIndex(0);
  if(temp != DEVICE_DISCONNECTED_C)   isNan = true;
  else                isNan = false;
  if (!isNan) {result = _last_t; return;}
  _last_t = temp;
  result = temp;
}
void DS18B20Class::read_temperatureF(float & result, boolean & isNan){
  _module->requestTemperatures(); 
  float temp = _module->getTempFByIndex(0);
  if(temp != DEVICE_DISCONNECTED_F)   isNan = true;
  else                isNan = false;
  if (!isNan) {result = _last_f; return;}
  _last_f = temp; 
  result = temp;
}

void DS18B20Class::get_json(JsonObject & root){
  float value_1;
  boolean state_1;
  JsonObject obj;

  read_temperature(value_1, state_1);
  obj = root.createNestedObject(F("c"));
  obj[F("value")] = value_1;
  obj[F("isNan")] = state_1;

  read_temperatureF(value_1, state_1);
  obj = root.createNestedObject(F("f"));
  obj[F("value")] = value_1;
  obj[F("isNan")] = state_1;

}
void DS18B20Class::domoticzJson(JsonObject & root){

}