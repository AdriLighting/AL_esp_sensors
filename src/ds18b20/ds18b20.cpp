/**
 * MIT License
 * 
 * Copyright (c) 2022 Adrien Grellard
 * 
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 * 
 * The above copyright notice and this permission notice shall be included in all
 * copies or substantial portions of the Software.
 * 
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
 */

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

  float temp = DEVICE_DISCONNECTED_C;

  while(1) {
    _module->requestTemperatures(); 
    temp = _module->getTempCByIndex(0);   
    if (temp != DEVICE_DISCONNECTED_C) {
      break;
    } 
    delay(0);
   } 

  if(temp != DEVICE_DISCONNECTED_C)   isNan = true;
  else                                isNan = false;

  if (!isNan) {
    result = _last_t; 
    return;
  }

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