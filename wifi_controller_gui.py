import tkinter as tk
import socket
import getopt, sys

class Controller:
    DEFAULT_PORT = 1111

    def __init__(self, ip):
        self.pressed = {}
        self.prevPressed = {}
        self._initPresses()
        self._create_ui()
        self._host = ip
        self._port = self.DEFAULT_PORT

    def _netcat(self, content):
        s = socket.socket(socket.AF_INET, socket.SOCK_DGRAM)
        s.sendto(content, (self._host, self._port))

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
        self._check_key_press()
        self.root.mainloop()

    def _check_for_press(self, key, command):
        if self._is_pressed(key):
            self.prevPressed[key] = True
            self._netcat(command)
            print(key + " pressed")

    def _check_for_release(self, key, command):
        if self._is_released(key):
            self.prevPressed[key] = False
            self._netcat(command)
            print(key + " released")

    def _check_key_press(self):
        self._check_for_press("w", b"\x01")
        self._check_for_release("w", b"\x02")
        self._check_for_press("s", b"\x03")
        self._check_for_release("s", b"\x04")
        self._check_for_press("d", b"\x05")
        self._check_for_release("d", b"\x06")
        self._check_for_press("a", b"\x07")
        self._check_for_release("a", b"\x08")

        self.root.after(20, self._check_key_press)

    def _is_pressed(self, key):
        return self.pressed[key] and self.prevPressed[key] == False

    def _is_released(self, key):
        return self.pressed[key] == False and self.prevPressed[key]

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

def main():
    try:
        opts, args = getopt.getopt(sys.argv[1:], "h:", ["host="])
    except getopt.GetoptError as err:
        print(str(err))
        usage()
        sys.exit(2)
    host = ""
    for o, a in opts:
        if o in ("-h", "--host"):
            host = a

    if host == "":
        print("Did not define host, use -h or --host to pass the host name of the car")
        sys.exit(2)

    p = Controller(host)
    p.start()

def usage():
    print("Available options:")
    print("-h, --host  Define RC car IP address")


if __name__ == "__main__":
    main()
