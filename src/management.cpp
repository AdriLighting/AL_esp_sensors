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

#include "management.h"

template <class T> 
void Sensor<T>::create (uint8_t p, uint8_t & r) {
  _list.add(new T(p));
  r = _list.size()-1;     
}

template <class T> 
void Sensor<T>::create (uint8_t p) {
  _list.add(new T(p));
}

template <class T> 
T * Sensor<T>::module(uint8_t pos) {
  return _list.get(pos);
}


template <class T> 
void Sensor<T>::get_json(JsonObject & obj, uint8_t p) {
  if (p<0) return;
  if (p>_list.size()) return;
  T * item = _list.get(p);
  JsonObject objPin = obj.createNestedObject(String(item->get_pin()));
  item->get_json(objPin);     
}



template <class T> 
boolean Sensor<T>::temperature_loop(const String & key, uint8_t p) {
  DynamicJsonDocument doc(1024);
  if (p<0) return false;
  if (p>_list.size()) return false;
  JsonObject root = doc.to<JsonObject>();
  _list.get(p)->get_json(root); 
  String v = root[key][F("value")].as<String>();
  if (_lastValue != v) {
    _lastValue = v;
    return true;    
  }
  return false;
}

template <class T>  
void Sensor<T>::temperature_read(uint8_t p, float & result, boolean & isNan) {
  if (p<0) return;
  if (p>_list.size()) return;
  _list.get(p)->read_temperature(result, isNan);      
}


template class Sensor< dht22Class >;
template class Sensor< DS18B20Class >;

