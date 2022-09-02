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

    void read_temperature         (float & result, boolean & isNan);
    void read_temperatureF        (float & result, boolean & isNan);
    void read_temperatureIndice   (float & result, boolean & isNan);
    void read_humidity            (float & result, boolean & isNan);

    void get_json     (JsonObject & root);
    void domoticzJson (JsonObject & root);
  };

#endif // DHT22_H