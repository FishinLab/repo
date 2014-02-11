#!/usr/bin/python 
#vim: tabstop = 4 shift = 4

import os
import sys
import commands
import re
import time
import subprocess
import signal
import socket

from subprocess import Popen

port = 8888
BUF_SIZE = 100000
time_limit = 10

def parse_ip_addr(fp):
    if not fp: 
        print >> sys.stderr, "no input file"
        return None 
    rx = re.compile("\d+.\d+.\d+.\d+") 
    addrs = fp.readlines(); fp.seek(0)
    filter_addrs = rx.findall(fp.read()) 
    if len(addrs) != len(filter_addrs):
        print >> sys.stderr, "ip addresses is not good"
        return None 
    return filter_addrs 

def triger(addr, res_dict):
    global port, time_limit
    if not addr:
        print >> sys.stderr, "addr is not good"
        return 
    p_pid = os.getpid(); c_pid = -1
    start_t = time.time()
    sock = socket.socket(socket.AF_INET, socket.SOCK_DGRAM)
#DEBUG:
    c_pid = os.fork()
    if c_pid:
        sock.connect((addr, int(port)))
        sock.sendall("begin")
        res_dict[addr] = sock.recv(BUF_SIZE)
    else:
        while(True):
            recv_data = sock.recvfrom(BUF_SIZE)
            if time.time() - start_t > time_limit or recv_data:
                #DEBUG:
                print >> sys.stdout, recv_data
                res_dict[addr] = recv_data 
                break
        sock.close()
    
#    try:
#        c_pid = os.fork()
#        if c_pid:
#            sock.connect((addr, int(port)))
#FIXME:
#   every client should only accept one server's request
#            sock.sendall("begin")
#            res_dict[addr] = sock.recv(BUF_SIZE)
#        else:
#            while(True):
#                if time.time() - start_t > time_limit: break
#FIXME:
#           os.kill(c_pid, signal.SIGHUP)
#            exit(1)
#    except:
        #DEBUG:
#        print >> sys.stderr, "error when triger the client script"
#    finally:
#       sock.close()

if "__main__" == __name__:
    time_limit = 100
    fp = file(sys.argv[1], "r") 
    addrs = parse_ip_addr(fp); fp.close()
    res_dict = {}

    for addr in addrs:
        res_dict[addr] = "bad"
        triger(addr, res_dict)

    for res in res_dict:
        print >> sys.stdout, (res, res_dict[res])
