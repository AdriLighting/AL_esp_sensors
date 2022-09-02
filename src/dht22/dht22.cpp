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

#include "dht22.h"

dht22Class::dht22Class(uint8_t pin) {
  _pin = pin;
  _module = new DHT(pin, DHT22);
  begin();
}
void dht22Class::begin(){
  _module->begin(); 
}
uint8_t dht22Class::get_pin() {return _pin;}
void dht22Class::read_temperature(float & result, boolean & isNan){
  float h = _module->readHumidity();
  float t = _module->readTemperature();
  float f = _module->readTemperature(true);
  if (isnan(h) || isnan(t) || isnan(f)) {isNan = false; result = _last_t; return;}
  isNan   = true;
  result  = t;
  _last_t = t;
}
void dht22Class::read_temperatureF(float & result, boolean & isNan){
  float h = _module->readHumidity();
  float t = _module->readTemperature();
  float f = _module->readTemperature(true);
  if (isnan(h) || isnan(t) || isnan(f)) {isNan = false; result = _last_f; return;}
  isNan   = true;
  result  = f;
  _last_f = f;
}
void dht22Class::read_temperatureIndice(float & result, boolean & isNan){
  float h = _module->readHumidity();
  float t = _module->readTemperature();
  float f = _module->readTemperature(true);
  if (isnan(h) || isnan(t) || isnan(f)) {isNan = false; result = _last_i; return;}
  isNan   = true;
  result  = _module->computeHeatIndex(t, h, false);
  _last_i = result;
}
void dht22Class::read_humidity(float & result, boolean & isNan){
  float h = _module->readHumidity();
  if (isnan(h)) {isNan = false; result = _last_h; return;}
  isNan   = true;
  result  = h;
  _last_h = h;
}
void dht22Class::get_json(JsonObject & root){
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

  read_temperatureIndice(value_1, state_1);
  obj = root.createNestedObject(F("i"));
  obj[F("value")] = value_1;
  obj[F("isNan")] = state_1;

  read_humidity(value_1, state_1);
  obj = root.createNestedObject(F("h"));
  obj[F("value")] = value_1;
  obj[F("isNan")] = state_1;


}
void dht22Class::domoticzJson(JsonObject & root){
  float value_1;
  float value_2;
  boolean state;
  read_temperature(value_1, state);
  read_humidity(value_2, state);

    int hum_stat = 0;
    if ( value_2 > 70 ) {
        hum_stat = 3;
    } else if ( value_2 < 30 ) {
        hum_stat = 2; 
    } else if ( (value_2 >= 3) && (value_2 <= 45) ) {
        hum_stat = 0;
    } else if ( (value_2 > 45) && (value_2 <= 70) ) {
        hum_stat = 1;
    }

  root[F("nvalue")] = 0;
  root[F("svalue")] = String(value_1) + ";" + String(value_2) + ";" + String(hum_stat);
}