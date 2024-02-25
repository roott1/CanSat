# The CanSat initiative
## Main ideas
The final goal of the project is to launch a CanSat using a high-altitude balloon.
## Hardware
<p>The main components of the CanSat are:
<dl>
  <dt>Arduino Uno board.</dt>
  <dd>INPUT/OUTPUT</dd>
  
  [ESP32](https://es.aliexpress.com/item/1005006161858012.html?spm=a2g0o.order_list.order_list_main.17.21ef194do5Kw3a&gatewayAdapt=glo2esp)
  <dd>Web Server.</dd>
  
  [NEO-6M](https://es.aliexpress.com/item/1005005504923225.html?spm=a2g0o.order_list.order_list_main.29.21ef194do5Kw3a&gatewayAdapt=glo2esp)
  <dd>GPS.</dd>
  
  [BME680](https://es.aliexpress.com/item/1005005970382773.html?spm=a2g0o.cart.0.0.57be7a9dQOGUTE&mp=1&gatewayAdapt=glo2esp)
  <dd>Digital sensor of temperature, humidity and pressure.</dd>
  
  [ADXL345 GY-291](https://es.aliexpress.com/item/1005005281279590.html?spm=a2g0o.cart.0.0.57be7a9dQOGUTE&mp=1&gatewayAdapt=glo2esp)
  <dd>Accelerometer.</dd>
</dl>

## Software
### About the Web Server
The [Web Server](https://codepen.io/Diego-Baeza/pen/NWJVZRj) is where you can easily visualize the information from the sensors.
<br>
Once HTML and CSS files are done they will be uploaded directly to ESP32 using SPIFFS. For now both are just in the Arduino IDE.
