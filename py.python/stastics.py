import os
import sys
import re

def stastics():
    fd_path = "/var/log/apache2/access.log"
    fd_con = ""
    if(os.path.exists(fd_path)):
        fd = file(fd_path, "r")
        fd_con = fd.read()
        fd.close()

    ip_grep = re.compile("\d+\.\d+\.\d+\.\d+")
    get_grep = re.compile("GET / HTTP/1.1")
    ip_arr = ip_grep.findall(fd_con)
    sta_sum_ip = 0
    sta_stack = {}
    for ip in ip_arr:
        if ip in sta_stack:
            sta_stack[ip] += 1
        else:
            sta_stack[ip] = 0
        sta_sum_ip += 1
    print >> sys.stdout, sta_sum_ip 
    for ip in sta_stack:
        print >> sys.stdout, ip
    print >> sys.stdout, ("number of accessed client's ip address ... => " ,len(sta_stack))

    get_arr = get_grep.findall(fd_con)
    sta_sum_get = 0
    for get in get_arr:
        sta_sum_get += 1
    print >> sys.stdout, ("number of GET method used by client to access the index.html of blog ... =>", sta_sum_get)

if "__main__" == __name__:
    stastics()
