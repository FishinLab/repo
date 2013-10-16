import os
import sys
import hashlib
import binascii
import base64

IGNORE = file("/dev/null", "w")

def encode_str_b64(source_str):
    global IGNORE
    return base64.encodestring(source_str)

def encode_str_complicated(source_str):
    global IGNORE
    pass

def encode_file_b64(source_fd, target_fd):
    global IGNORE
    if(source_fd.closed or target_fd.closed): return false
    base64.encode(source_fd, target_fd) 

def encode_file_complicated(source_fd, target_fd):
    global IGNORE
    if(source_fd.closed or target_fd.closed): return false
    tmp_fd = file("".join([os.getcwd(), os.sep, "tmp_encode_f"]), "w")
    base64.encode(source_fd, tmp_fd)
    
    tmp_l_arr = []
    for l in tmp_fd.readlines():
        tmp_l_arr.append(binascii.b2a_hex(l))

    target_fd.writelines(tmp_l_arr)  

def decode_str_b64(source_str):
    global IGNORE
    return base64.decodestring(source_str)

def decode_str_complicated(source_str):
    global IGNORE
    pass

def decode_file_b64(source_fd, target_fd):
    global IGNORE
    if(source_fd.closed or target_fd.closed): return false
    base64.decode(source_fd, target_fd)

def decode_file_complicated(source_fd, target_fd):
    global IGNORE
    if(source_fd.closed or target_fd.closed): return false
    tmp_fd = file("".join([os.getcwd(), os.sep, "tmp_decode_f"]), "w")
    base64.decode(source_fd, tmp_fd)

    tmp_l_arr = []
    for l in tmp_fd.readlines():
        tmp_l_arr.append(binascii.a2b_hex(l))
    target_fd.writelines(tmp_l_arr)

if "__main__" == __name__: 
    if("ess" == sys.argv[1]):
        source_str = sys.argv[2]
        target_str = encode_str_b64(source_str)
#DEBUG:
        print >> sys.stdout, target_str 
    elif("esc" == sys.argv[1]):
        pass
    elif("efs" == sys.argv[1]):
        if(os.path.exists(sys.argv[2]) and os.path.exists(sys.argv[3])):
            source_fd = file(sys.argv[2], "r")
            target_fd = file(sys.argv[3], "w")
            encode_file_b64(source_fd, target_fd)
    elif("efc" == sys.argv[1]):
        if(os.path.exists(sys.argv[2]) and os.path.exists(sys.argv[3])):
            source_fd = file(sys.argv[2], "r")
            target_fd = file(sys.argv[3], "w")
            encode_file_complicated(source_fd, target_fd)
    elif("dss" == sys.argv[1]):
        source_str = sys.argv[2]
        target_str = encode_str_b64(source_str)
#DEBUG:
        print >> sys.stdout, target_str 
    elif("dsc" == sys.argv[1]):
        pass
    elif("dfc" == sys.argv[1]):
        if(os.path.exists(sys.argv[2]) and os.path.exists(sys.argv[3])):
            source_fd = file(sys.argv[2], "r")
            target_fd = file(sys.argv[3], "w")
            decode_file_complicated(source_fd, target_fd)
    elif("dfc" == sys.argv[1]):
        if(os.path.exists(sys.argv[2]) and os.path.exists(sys.argv[3])):
            source_fd = file(sys.argv[2], "r")
            target_fd = file(sys.argv[3], "w")
            decode_file_complicated(source_fd, target_fd)
