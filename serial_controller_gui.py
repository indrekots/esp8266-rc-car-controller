import tkinter as tk
import serial


class Controller:
    def __init__(self):
        # this dict keeps track of keys that have been pressed but not
        # released
        self.pressed = {}
        self._create_ui()

    def start(self):
        self._checkKeyPress()
        self.root.mainloop()

    def _checkKeyPress(self):
        if self.pressed["w"]:
            print("forwards")
        elif self.pressed["d"]:
            print("right")
        elif self.pressed["a"]:
            print("left")
        elif self.pressed["s"]:
            print("backwards")
        else:
            print("no command")

        self.root.after(10, self._checkKeyPress)

    def _create_ui(self):
        self.root = tk.Tk()
        self.root.geometry('800x600')
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
