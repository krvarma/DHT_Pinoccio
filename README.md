Pinoccio and DHT22 Sensor
-------------------------

Here is a sample application that uses Pinoccio and DHT22 Temperature and Humidity sensor. The application uses Arduino DHT22 Library to read the sensor. For this sample Arduino IDE is used to compile the source code.

The sample application registers two Bitlash function `DHT22.temperature` and `DHT22.humidity, these can be accessed from Pinoccio HQ. The application also reports the sensor value to the HQ periodically so that the other applications can use the live stream to display the sensor values. Following snippet from the source code reports the sensor values to HQ:

    void reportToHQ(int temperature, int humidity){
      // Report temperature and humidity to HQ
      StringBuffer report(100);
      report.appendSprintf("[%d,[%d, %d],[%d, %d]]",
              keyMap("DHT22", 0),
              keyMap("t", 0),
              keyMap("h", 0),
              (int)(odht.temperature * 100),
              (int)(odht.humidity * 100));
              
      Scout.handler.report(report); 
    }
    
**Wiring**

 1. DHT22 Vcc to Pinoccio 3.3V 
 2. DHT22 Gnd to Pinoccio GND 
 3. DHT22 SIG to Pinoccio D4
 
**Screenshot**

![enter image description here][1]

![enter image description here][2]


  [1]: https://raw.githubusercontent.com/krvarma/DHT_Pinoccio/master/screenshot/hq.png
  [2]: https://raw.githubusercontent.com/krvarma/DHT_Pinoccio/master/screenshot/stream.png