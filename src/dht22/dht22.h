#ifndef DHT22_H
#define DHT22_H
	#include <Arduino.h>
	#include <ArduinoJson.h>
	#include <Adafruit_Sensor.h> // https://github.com/adafruit/Adafruit_Sensor.git
	#include <DHT.h> // https://github.com/adafruit/DHT-sensor-library.git
	#include <LinkedList.h>



	class dht22Class {
		DHT  * _module;
		float _last_t = 0;
		float _last_h = 0;
		float _last_f = 0;
		float _last_i = 0;
		uint8_t _pin = 0;
	public:
		dht22Class(uint8_t pin);
		~dht22Class(){};
		
		uint8_t get_pin();

		void begin();

		void read_temperature 				(float & result, boolean & isNan);
		void read_temperatureF 				(float & result, boolean & isNan);
		void read_temperatureIndice		(float & result, boolean & isNan);
		void read_humidity 						(float & result, boolean & isNan);

		void get_json			(JsonObject & root);
		void domoticzJson	(JsonObject & root);
	};

#endif // DHT22_H