import network
import nvs
from pixels import Pixels

#wlan = network.WLAN(network.STA_IF) # create station interface
#wlan.active(True)       # activate the interface
#wlan.scan()             # scan for access points
#wlan.isconnected()      # check if the station is connected to an AP
#wlan.connect('essid', 'password') # connect to an AP
#wlan.config('mac')      # get the interface's MAC adddress
#wlan.ifconfig()         # get the interface's IP/netmask/gw/DNS addresses

#ap = network.WLAN(network.AP_IF) # create access-point interface
#ap.config(essid='ESP-AP') # set the ESSID of the access point
#ap.active(True)         # activate the interface

#p = Pixels(16)

def connect(ssid, password):
    import network
    import nvs
    wlan = network.WLAN(network.STA_IF)
    wlan.active(True)
    if not wlan.isconnected():
        p.wifi_connecting()
        print('connecting to network...')
        wlan.connect(ssid, password)
        while not wlan.isconnected():
            pass
    print('network config:', wlan.ifconfig())