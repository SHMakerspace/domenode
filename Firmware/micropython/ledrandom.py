import machine, neopixel, random, time
import math
np = neopixel.NeoPixel(machine.Pin(16), 7, timing=True)

def blinky(np):
	n = np.n
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
	time.sleep_ms(random.randint(50, 200))


def clear(np):
	n = np.n
	for i in range(n):
		np[i] = (0, 0, 0)
		np.write()
		
		
def larson(np):
	n = np.n
	REDS = [0, 0, 0, 0, 0, 16, 64, 255, 64, 16, 0, 0, 0, 0, 0, 0]
	start_time = time.time()
	while True:
		delta = (time.time() - start_time) * 16
		offset = int(abs((delta % len(REDS)) - n))
	
		for i in range(n):
			np[i] = (REDS[offset + i], 0, 0)
	np.write()
	time.sleep_ms(100)
	
	
def big(np):
	n=np.n
	for i in range(n):
		r = random.randint(0, 255)
		g = random.randint(0, 255)
		b = random.randint(0, 255)
		
		np[i] = (r, g, b)
	np.write()
	time.sleep_ms(random.randint(100,200))
	
	
	