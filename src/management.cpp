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

