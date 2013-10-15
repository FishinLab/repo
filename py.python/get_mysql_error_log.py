#this is the script for getting the mysql error log from server when the log file is too long
import sys
import os

def check_log():

    if(os.path.exists('/var/log/mysql/error.log')):
        
        fd = file('/var/log/mysql/error.log' , 'r');
        line_num = fd.read().split('\n');
        fd.close();
        if(line_num >= 200):
            return True
        else:
            return False
    else:
        return False


def rsync_log():
    
    if(os.path.exists('/var/log/mysql/error.log')):
        os.system('cp /var/log/mysql/error.log /var/www/mysql/error.log')
        os.system('chmod 757 /var/www/mysql/error.log')

def run():

    if(check_log() is True):
        rsync_log()

if __name__ == '__main__':
    run()
    
