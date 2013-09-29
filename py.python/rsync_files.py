import os
import sys
import time
import MySQLdb
import commands
import subprocess
import signal

from subprocess import Popen
IGNORE = file("/dev/null", "w")

def rsync_file_and_update_info(user_id):
    f_pathes = os.listdir(os.path.join("/var/www/u/" , str(user_id), "tmp/"))
    conn = MySQLdb.connect()
    try:
        for f in f_pathes:
            get_info_sql = "".join(["select id from file_table where owner_id = ", str(user_id), " and file_name = ", f])
            o_cur = conn.cursor()
            o_cur.execute(get_info_sql)
            o_res = o_cur.fetch_all()

            target_p = "".join(["slave_node:/home/file_sys/", user_id, "files/"])        
            update_info_sql = "".join(["update file_table set file_path = ", target_p, " where id = ", o_res["id"]])
            pid = os.fork()
            if(0 == pid):
                p_rsync = Popen(["rsync", "-avz", f_pathes + os.sep + f, target_p], stdin = sys.stdin, stdout = sys.stdout, stderr = sys.stderr) 
                #p_rsync.communicate()
                p_rsync.terminate()
                os.kill(os.getpid(), signal.SIGHUP)
            else:
                o_cur.execute(update_info_sql)
                print >> IGNORE, commands.getoutput("rm -fR " + f)  
    except Exception as ex:
        print >> sys.stderr, str(ex) 
    finally:
        conn.close()

def get_files_info(user_id):
    f_pathes = os.listdir(os.path.join("/var/www/tmp/", str(user_id)))
    conn = MySQLdb.connect("localhost", "root", "mysql", "pixel_test")
    for f in f_pathes:
        get_info_sql = "select id, file_name, file_path from file_table where file_name = " + f;
        o_cur = conn.cursor()
        o_cur.execute(get_info_sql)
        o_res = o_cur.fetch_all()

        target_p = "".join(["slave_node:/home/file_sys/", str(user_id), os.sep, o_res["file_name"]])
        update_info_sql = "".join(["update file_table set file_path = ", target_p ," where id = ", o_res["id"]])
        o_cur.execute(update_info_sql)
        rsync_files(file_name, f, target_p) 
    conn.close()

def rsync_files(file_name, source_p, target_p):
#FIXME:
#here need auto autherization for root login
    cmd = "".join(["rsync -avz ", source_p, "root@", target_p])
    rsync_output = commands.getoutput(cmd) 

#commands' error handling     

if "__main__" == __name__:
    rsync_file_and_update_info(1) 
