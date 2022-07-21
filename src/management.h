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
    String _lastValue;
  public:

    Sensor(){};
    ~Sensor(){};

    void create (uint8_t p, uint8_t & r);
    void create (uint8_t p);


    void get_json(JsonObject & obj, uint8_t p = 0);

    boolean temperature_loop(const String & v, uint8_t pos = 0);
    void    temperature_read(uint8_t p, float & result, boolean & isNan);
    
    T * module(uint8_t pos);
  };

#endif // MANAGEMENT_H