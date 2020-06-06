# Neopixel definitions and functions

from machine import Pin
from neopixel import NeoPixel


class Pixels:

    def __init__(self, io)

    pin = Pin(io, Pin.OUT) # Set GPIO16 to output to drive NeoPixels
    np = NeoPixel(pin, 9) # Create NeoPixel driver on GPIO16 for 9 pixels
    n = np.n

    ## Examples
    #np[0] = (255, 255, 255) # Set the first pixel to white
    #np.write()
    #r, g, b = np[0]

    @staticmethod
    # Custom Animations

    def pixset(pixel, r, g, b):
        np[pixel] = (r, g, b)
        np.write()

    def clear():
        # clear
        for i in range(n):
            np[i] = (0, 0, 0)
        np.write()

    def wifi_connecting():
        np[0] = (255, 255, 0)
        np.write()
        time.sleep_ms(200)
        self.clear()

    def cycle():
        # cycle
        for i in range(4 * n):
            for j in range(n):
                np[j] = (0, 0, 0)
            np[i % n] = (255, 255, 255)
            np.write()
            time.sleep_ms(200)

    def bounce():
        for i in range(4 * n):
            for j in range(n):
                np[j] = (0, 0, 128)
            if (i // n) % 2 == 0:
                np[i % n] = (0, 0, 0)
            else:
                np[n - 1 - (i % n)] = (0, 0, 0)
            np.write()
            time.sleep_ms(150)

    def fade():
        for i in range(0, 4 * 256, 8):
            for j in range(n):
                if (i // 256) % 2 == 0:
                    val = i & 0xff
                else:
                    val = 255 - (i & 0xff)
                np[j] = (val, 0, 0)
            np.write()
            time.sleep_ms(25)

    def bright():
        for i in range(n):
            np[i] = (255, 255, 255)
        np.write()
        
    def touchOn():
        cutoff = 100
        touch = TouchPad(Pin(14))
        while True:
            if touch.read() < 100:
                for i in range(n):
                    np[i] = (128, 0, 127)
                np.write()
            else:
                for i in range(n):
                    np[i] = (0, 0, 0)
                np.write()

    def blinky():
        pixel = random.randint(1, 7)
        for i in range(n):
            if i == pixel:
                r = random.randint(0, 255)
                g = random.randint(0, 255)
                b = random.randint(0, 255)
                np[i] = (r, g, b)
            else:
                np[i] = (0, 0, 0)
        np.write()
        time.sleep_ms(random.randint(100, 300))

    def larson():
        REDS = [0, 0, 0, 0, 0, 16, 64, 255, 64, 16, 0, 0, 0, 0, 0, 0]
        start_time = time.time()
        while True:
            delta = (time.time() - start_time) * 16
            offset = int(abs((delta % len(REDS)) - n))
        
            for i in range(n):
                np[i] = (REDS[offset + i], 0, 0)
        np.write()
        time.sleep_ms(100)
        
            def big():
        for i in range(n):
            r = random.randint(0, 255)
            g = random.randint(0, 255)
            b = random.randint(0, 255)
            
            np[i] = (r, g, b)
        np.write()
        time.sleep_ms(random.randint(100,200))