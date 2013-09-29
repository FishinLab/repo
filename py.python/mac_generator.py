import sys
import random
import hashlib
import os

def generate_new_mac(hw):
     
    hws = hw.split(":")
    for h in hws:
        hw += h
    
    new_hw = ""
    sha1_obj = hashlib.sha1(hw)
    hw_hex = sha1_obj.hexdigest()

    for i in range(0, 17, 3):
        new_hw += hw_hex[i] + hw_hex[i + 1] + ":"

    return new_hw[0:len(new_hw) - 1]
