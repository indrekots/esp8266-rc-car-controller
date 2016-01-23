import tkinter as tk
import serial

class Controller:
    def __init__(self):
        self.pressed = {}
        self.prevPressed = {}
        self._initPresses()
        self._create_ui()
        self.ser = serial.Serial(
            port='/dev/ttyACM0',
            baudrate=115200,
            parity=serial.PARITY_ODD,
            stopbits=serial.STOPBITS_TWO,
            bytesize=serial.SEVENBITS
        )
        self.ser.isOpen()

    def _initPresses(self):
        self.pressed["w"] = False
        self.pressed["a"] = False
        self.pressed["s"] = False
        self.pressed["d"] = False
        self.prevPressed["w"] = False
        self.prevPressed["a"] = False
        self.prevPressed["s"] = False
        self.prevPressed["d"] = False


    def start(self):
        self._checkKeyPress()
        self.root.mainloop()

    def _checkKeyPress(self):
        if self.pressed["w"] and self.prevPressed["w"] == False:
            self.prevPressed["w"] = True
            self.ser.write(b"\x01")
            print("forward pressed")

        if self.pressed["w"] == False and self.prevPressed["w"]:
            self.prevPressed["w"] = False
            self.ser.write(b"\x02")
            print("forward released")

        if self.pressed["s"] and self.prevPressed["s"] == False:
            self.prevPressed["s"] = True
            self.ser.write(b"\x03")
            print("backwards pressed")

        if self.pressed["s"] == False and self.prevPressed["s"]:
            self.prevPressed["s"] = False
            self.ser.write(b"\x04")
            print("backwards released")

        if self.pressed["d"] and self.prevPressed["d"] == False:
            self.prevPressed["d"] = True
            self.ser.write(b"\x05")
            print("right pressed")

        if self.pressed["d"] == False and self.prevPressed["d"]:
            self.prevPressed["d"] = False
            self.ser.write(b"\x06")
            print("right released")

        if self.pressed["a"] and self.prevPressed["a"] == False:
            self.prevPressed["a"] = True
            self.ser.write(b"\x07")
            print("left pressed")

        if self.pressed["a"] == False and self.prevPressed["a"]:
            self.prevPressed["a"] = False
            self.ser.write(b"\x08")
            print("left released")

        self.root.after(10, self._checkKeyPress)

    def _create_ui(self):
        self.root = tk.Tk()
        self.root.geometry('400x300')
        self._set_bindings()

    def _set_bindings(self):
        for char in ["w","s","d", "a"]:
            self.root.bind("<KeyPress-%s>" % char, self._pressed)
            self.root.bind("<KeyRelease-%s>" % char, self._released)
            self.pressed[char] = False

    def _pressed(self, event):
        self.pressed[event.char] = True

    def _released(self, event):
        self.pressed[event.char] = False

if __name__ == "__main__":
    p = Controller()
    p.start()
