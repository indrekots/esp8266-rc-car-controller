#Control an RC car with ESP8266 over WiFi

This repository contains code to control an RC car using an ESP8266 board with your regular keyboard. For more information head over to [this blog post](http://blog.indrek.io/articles/how-to-control-an-rc-car-over-wifi-with-esp8266/) to see how to set up an RC car.

##Requirements

* Python 3
* Arduino IDE

##Example usage

Open `esp8266-rc-car` with your Arduino IDE and upload the sketch to your Arduino board. Make sure to enter your WiFi SSID and password in the header of the file.

```
const char* ssid = "SSID"; //Enter your wifi network SSID
const char* password = "PASSWORD"; //Enter your wifi network password
```

Open `serial_controller_gui.py` with a text editor and change the serial port in the constructor to match your needs. Then run the script with:

```bash
python serial_controller_gui.py
```

Press W, A, S, D keys to control your RC car.
