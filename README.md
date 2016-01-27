#Control an RC car with Arduino

This repository contains code to control an RC car using an Arduino with your regular keyboard. For more information head over to [this blog post](http://blog.indrek.io/articles/controlling-an-rc-car-with-arduino/) to see how to set up the electronic circuit.

##Requirements

* Python 3
* Arduino IDE

##Example usage

Open `rc-car-arduino` with your Arduino IDE and upload the sketch to your Arduino board.

Open `serial_controller_gui.py` with a text editor and change the serial port in the constructor to match your needs. Then run the script with:

```bash
python serial_controller_gui.py
```

Press W, A, S, D keys to control your RC car.
