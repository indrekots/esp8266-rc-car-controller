#Control an RC car with ESP8266 over WiFi

This repository contains code to control an RC car over WiFi using an ESP8266 board. For more information head over to [this blog post](http://blog.indrek.io/articles/how-to-control-an-rc-car-over-wifi-with-esp8266/) to see how to set up an RC car.

##Requirements

* Python 3
* Arduino IDE

##Example usage

Open `esp8266-rc-car` with your Arduino IDE and upload the sketch to your Arduino board. Make sure to enter your WiFi SSID and password in the header of the file.

```cpp
const char* ssid = "SSID"; //Enter your wifi network SSID
const char* password = "PASSWORD"; //Enter your wifi network password
```

Open your terminal and run the python script with

```bash
python wifi_controller_gui.py --host=<IP address of the car>
```

Press W, A, S, D keys to control your RC car.
