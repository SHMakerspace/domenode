import networking
import pixels
import nvs

from ota_update.main.ota_updater import OTAUpdater

# Get SSID
ssid = nvs.retrieve_str(ssid)
# Get pass
password = nvs.retrieve_str(password)

# Git URL
giturl = 'https://github.com/SHMakerspace/domenode'
def boot():
    # Check against SHM Git for new release
    o = OTAUpdater(giturl)
    o.download_and_install_update_if_available(ssid, wifi-password)


def start():
     # Connect to WiFi
     networking.connect(ssid, password)
     # Connect CAN
     # Connect MQTT
     # Log initial messages to MQTT - node name, version, IP, status etc.

     # Set 'default' mode

     # Enter main loop
        # Check onboard (cap touch, sensors)
        # Check CAN messages
        # Check WiFi messages



boot()