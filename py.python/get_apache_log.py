#this is the script for user to get apache server log
import sys
import os

def check_log():

    if(os.path.exists('/var/log/apache2/error.log') and os.path.exists('/var/log/apache2/access.log')):
        return True
    else:
        return False

def rsync_log():
    
    os.system('tail -50 /var/log/apache2/error.log > /var/www/apache2/error.log &')
    os.system('chmod 757 /var/www/apache2/error.log')

    os.system('tail -200 /var/log/apache2/access.log > /var/www/apache2/access.log &')
    os.system('chmod 757 /var/www/apache2/access.log')

def run():
    if (check_log()):
        rsync_log()

if __name__ == '__main__':
    run()
