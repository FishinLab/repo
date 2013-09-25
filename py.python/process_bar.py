#!/bin/python
#vim: shiftstop=4 tab=4

import os
import sys
import time

def show_process(count, stop_condition):
    if None == count:
        count = 0

    while count < stop_condition:
        count = count + 1
        prog_str = "".join([(count * "#"), ((stop_condition - count) * " "), "]"]) 
        os.write(1, "\r[%s" % prog_str) 
        sys.stdout.flush()
        time.sleep(0.1)

if __name__ == "__main__":
    count = 0
    stop_condition = 30
    show_process(count, stop_condition)
