# Works with non-volatile storage (NVS)

import machine

# Get saved integer key
node_id = machine.nvs_getint('node_id')
