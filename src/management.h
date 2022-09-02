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