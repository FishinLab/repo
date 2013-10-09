import dos
import sys
import subprocess
from subprocess import Popen

class ddoser(object):
    def __init__(self, doser_num = 3):
        self.dosers = []
        self.doser_num = doser_num

    def attack(self):
        IGNORE = open("/dev/null", "w")
        doser_kid = Popen(["python", "./dos.py"], stdout = IGNORE, stderr = sys.stdout)
        self.dosers.append(doser_kid)        
        IGNORE.close()

def run(doser_num):
    obj_ddoser = ddoser(doser_num)
    if(int(doser_num)):
        obj_ddoser.attack()

if "__main__" == __name__:
    run(int(sys.argv[1]))

