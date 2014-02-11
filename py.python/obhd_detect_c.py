#!/usr/bin/python
#vim: tapstop = 4 shift = 4

import os
import sys 
import commands
import socket
import time
import re

port = 8888
BUF_SIZE = 1000000

def detect_os_version():
    return os.uname()[0]

def detect_speed(dev):
    #main: dd if = dev of = dev count = blocks 
    count = 1024
    data = commands.getoutput("".join(["dd if=/dev/", dev, " of=/dev/", dev, " count=", str(count)])).splitlines()[-1] 
    return data 

def detect_device():
    devices = []
    if detect_os_version() in ("Redhat", "Ubuntu", "SUSE", "Linux"):
        mount_fd = file("/proc/mounts", "r")
        data_lines = mount_fd.readlines()
        mount_fd.close()
#        data_lines = commands.getoutput("".join(["mount"])).splitlines()
        for line in data_lines:
#FIXME:
#   use regular express instread of substring
#            if "/dev/sd" in line: 
#                devices.append(line.split("/dev/")[1])
#                print >> sys.stdout, devices
            rx = re.compile("")
            devices.append(rx.findall(line)[0]) 
    return devices
        
def go(devices):
    global port
    sock = socket.socket(socket.AF_INET, socket.SOCK_DGRAM) 
    sock.bind(('', int(port))) 
    
    try:
        while(True):
            mess, addr = sock.recvfrom(BUF_SIZE)
            if "begin" == mess:
                #DEBUG:
                print >> sys.stdout, "triger recieved"
                for dev in devices:
                    dev_data = detect_speed(dev)
                    #DEBUG:
                    print >> sys.stdout, dev_data
                    sock.sendto(dev_data, addr)
    except KeyboardInterrupt:
        print >> sys.stdout, "stop daemon process" 
    finally:
        sock.close()

if "__main__" == __name__:
    go(detect_device())

