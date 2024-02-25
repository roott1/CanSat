# The CanSat initiative
## Main ideas
The final goal of the project is to launch a CanSat using a high-altitude balloon.
## Hardware
<p>The main components of the CanSat are:
<dl>
  <dt>Arduino Uno board.</dt>
  <dd>For INPUT/OUTPUT</dd>
  <dt>ESP32 or ESP32-CAM.</dt>
  <dd>For the Web Server</dd>
  <dt>NEO-6M</dt>
  <dd>GPS</dd>
  <dt>BME680</dt>
  <dd>Digital sensor of temperature, humidity and pressure</dd>
  <dt>ADXL345 GY-291</dt>
  <dd>Accelerometer</dd>
</dl>

## About the Web Server
The [Web Server](https://codepen.io/Diego-Baeza/pen/NWJVZRj) is where you can easily visualize the information from the sensors.
<br>
Once HTML and CSS files are done they will be uploaded directly to ESP32 using SPIFFS.
<br>
For now it's just in the Arduino IDE
