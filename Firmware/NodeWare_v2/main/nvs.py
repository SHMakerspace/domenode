# Works with non-volatile storage (NVS)
import machine

def retrieve_int(integer)
    # Get saved integer key
    return machine.nvs_getint(integer)

def retrieve_str(string)
    return machine.nvs_getstr(string)
