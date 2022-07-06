#include "management.h"

template <class T> 
void Sensor<T>::create (uint8_t p, uint8_t & r) {
	_list.add(new T(p));
	r = _list.size()-1;			
}
template <class T> 	
void Sensor<T>::read_temperature(uint8_t p, float & result, boolean & isNan) {
	if (p<0) return;
	if (p>_list.size()) return;
	_list.get(p)->read_temperature(result, isNan);			
}
template <class T> 
void Sensor<T>::get_json(uint8_t p, JsonObject & obj) {
	if (p<0) return;
	if (p>_list.size()) return;
	T * item = _list.get(p);
	JsonObject objPin = obj.createNestedObject(String(item->get_pin()));
	item->get_json(objPin);			
}
template <class T> 
T * Sensor<T>::module(uint8_t pos) {
	return _list.get(pos);
}
template class Sensor< dht22Class >;
template class Sensor< DS18B20Class >;

