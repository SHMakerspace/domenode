from machine import TouchPad, Pin
touch = TouchPad(Pin(14))


touch.read()              # Returns a smaller number when touched