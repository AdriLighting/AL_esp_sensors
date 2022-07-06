#ifndef MANAGEMENT_H
#define MANAGEMENT_H
	#include <Arduino.h>
	#include <ArduinoJson.h>
	#include <LinkedList.h>

	#include "dht22/dht22.h"
	#include "ds18b20/ds18b20.h"

	template <class T> 
	class Sensor
	{
		LList<T *> _list;
	public:

		Sensor(){};
		~Sensor(){};

		void create (uint8_t p, uint8_t & r);

		void read_temperature(uint8_t p, float & result, boolean & isNan);

		void get_json(uint8_t p, JsonObject & obj);
		
		T * module(uint8_t pos);
	};

#endif // MANAGEMENT_H