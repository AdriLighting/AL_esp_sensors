#ifndef DS18B20_H
#define DS18B20_H
	#include <Arduino.h>
	#include <ArduinoJson.h>
	#include <OneWire.h> // https://github.com/PaulStoffregen/OneWire.git
	#include <DallasTemperature.h> // https://github.com/milesburton/Arduino-Temperature-Control-Library.git
	#include <LinkedList.h>

	class DS18B20Class
	{
		OneWire  			* _whire;
		DallasTemperature  	* _module;
		float _last_t = 0;
		float _last_f = 0;
		uint8_t _pin = 0;
	public:
		DS18B20Class(uint8_t pin);
		~DS18B20Class(){};
		
		uint8_t get_pin();
		void begin 				();
		void read_temperature 				(float & result, boolean & isNan);
		void read_temperatureF 				(float & result, boolean & isNan);

		void get_json			(JsonObject & root);
		void domoticzJson	(JsonObject & root);
	};



#endif // DS18B20_H