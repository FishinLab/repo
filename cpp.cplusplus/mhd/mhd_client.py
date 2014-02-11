import os
import sys
import urllib
import urllib2
import httplib
import httplib2
import time
import socket
import traceback

def go_client(url, port):
    if url is None: return
    port = int(port)
    try:
        while(True):
            post_data = {
                    "suicide":urllib.urlencode({"request": "suicide"}),
                    "status":urllib.urlencode({"request": "status"}),
                    "init":urllib.urlencode({"request": "init"}),
                    "info":urllib.urlencode({"request": "info"})
                    }
            os.system("python ./process_bar.py 'connecting localhost...' 15")

            head = {"Content-type": "application/x-www-form-urlencoded", "Accept":"text/plain", 
            #head = {"Content-type": "multipart/form-data", "Accept":"text/plain", 
                    "sql_line":"@create table data_reboot (card_no int not null primary key, name varchar(256))"}
            http = httplib.HTTPConnection(url, port, timeout = 60)
            http.request("POST", "/", post_data["suicide"], head)

            resp = http.getresponse()
            print >> sys.stdout, "----------[STATUS]----------"
            print >> sys.stdout, resp.status
            print >> sys.stdout, "----------[REASON]----------"
            print >> sys.stdout, resp.reason
            print >> sys.stdout, "----------[HEADER]----------"
            headers =  resp.getheaders()
            for h in headers:
                print >> sys.stdout, h
            print >> sys.stdout, "----------[BODY]----------"
            print >> sys.stdout, resp.read()
            http.close()
            os.system("python ./process_bar.py disconnecting... 30")
            time.sleep(10)
    except Exception as e:
        print >> sys.stderr, str(e)

if "__main__" == __name__:
    url = "127.0.0.1"
    port = 8888
    go_client(url, port) 
