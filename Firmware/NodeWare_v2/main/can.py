from machine import CAN
# From nos86 MicroPython integration work (see https://github.com/micropython/micropython/pull/5310)

# Construct a CAN bus  (pins of DomeNode CTX = IO5, CRX = IO4)
bus = CAN(tx=5, rx=4, baudrate=500, mode=CAN.MODE_NO_ACK)

# Send a self message
bus.send([0,1,2,3], 0x86, self_flag=True)
bus.recv()