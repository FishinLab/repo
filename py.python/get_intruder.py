#this script help user to get out intruder from the auth.log 

import sys
import os
import re

class police_man:

    intruder = [];
    
    def get_intruder(self):
        
        rpx = "Failed password for root from \d+.\d+.\d+.\d+";
        intruder_ip = "\d+.\d+.\d+.\d+"
        tmp_ips = []
        ips = []

        if(os.path.exists("/var/log/auth.log")):
            fd = open("/var/log/auth.log" , "r")
            fd.seek(0);
            tmp_ips = re.findall(rpx , fd.read() , 0);
        else:
            print "the auth.log file can not be found"
            return False

        for ip in tmp_ips:
            ips.append(re.findall(intruder_ip , ip)[0])
            
        #ips.sort()
        c = 0
        for c in range(len(ips)):
            if(ips.count(ips[c]) >= 2):
                print >> sys.stdout, ips[c] 
                c += ips.count(ips[c]) - 1
        return True

def run():
    pm = police_man()
    pm.get_intruder()
        
if __name__ == "__main__":
    run()
