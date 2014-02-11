#include <iostream>
#include <string.h>
#include <math.h>
//#include <mysql++.h>
#include <regex.h>
#include <stdlib.h>

extern "C" {
#include <lua.h>
#include <lualib.h>
#include <lauxlib.h>

#include <microhttpd.h> 
}

//#include "translator.h"
#include "mhd.h"

using namespace std;

struct Request{
    MHD_PostProcessor* pp;
    const char* post_url;
    bool has_parsed;
};

int init_mdh(){
    return 0;        
}

//this handle_error function should come from translator.cpp
int handle_error(){
    return 0;
}

int do_echo(MHD_Connection* conn){
    //DEBUG:
    fprintf(stdout, "in do_echo\n");
    int suc = LADON_SUCCESS;
    fprintf(stdout, "get test data which HTTP method is GET\n");
    const char* resp_data = "<html><title>MHD</title><body>Fuck yeah!</body></html>";
    MHD_Response* resp = MHD_create_response_from_buffer(strlen(resp_data), (void*)resp_data, MHD_RESPMEM_PERSISTENT); 
    suc = MHD_queue_response(conn, MHD_HTTP_OK, resp);
    fprintf(stdout, "in do_echo suc: %d\n", suc);
    MHD_destroy_response(resp);
    fprintf(stdout, "in do echo response data has been queued\n");

    return MHD_YES;
}

static int do_post_iterator(void* cls, enum MHD_ValueKind kind, const char* key, const char* filename, const char* content_type, 
        const char* transfer_encoding, const char* data, long long unsigned int off, unsigned int size){

    int suc = LADON_SUCCESS;
    Request* req = (Request*)cls;
    fprintf(stdout, "in do_post_iterator %s\n", req->post_url);
    fprintf(stdout, "in do_post_iterator data %s\n", data);
    if(0 == strncmp("DONE", key, strlen(key))){
        fprintf(stdout, "in do_post_iterator and the key is %s\n", key); 
    }
    return MHD_YES;
}

int do_parse_post_data(Request* req, const char* resp_data){

    int suc = LADON_SUCCESS;
    //do parse user post data and init lua translator
    //
    return suc;
}

static int do_answer(void* cls, MHD_Connection* conn, const char* url, const char* method, const char* version, 
        const char* data, size_t* data_size, void** ptr){

    int suc = LADON_SUCCESS;

    //DEBUG:
    fprintf(stdout, "in do_answer method %s\n", method);
    fprintf(stdout, "in do_answer url %s\n", url);
    //now ptr should be NULL
    Request* req = new Request;

    if(NULL == *ptr){
        //DEBUG:
        fprintf(stdout, "in do_answer first callback\n");
        *ptr = req; 
        if(0 == strncmp(method, MHD_HTTP_METHOD_POST, strlen(method))){
            req->post_url = url;
            req->pp = MHD_create_post_processor(conn, 1024, &do_post_iterator, req);       
            if(NULL == req->pp){
                suc = handle_error();
                //DEBUG:
                fprintf(stderr, "in do_answer could not create post processor\n");
            }
        }//else do_echo(conn);
    }
    else  
    if(0 == strncmp(method, MHD_HTTP_METHOD_POST, strlen(method))){
        //DEBUG:
        fprintf(stdout, "in do_answer second callback\n");
        req = (Request*)*ptr;
        if(0 == strncmp(method, MHD_HTTP_METHOD_POST, strlen(method))){
            if(NULL == data){
                suc = handle_error(); 
                fprintf(stderr, "in do_answer why data is null?%s\n", data);
            }else{
                MHD_post_process(req->pp, data, *data_size); 
            }
            //if(LADON_SUCCESS == suc)  MHD_post_process(req->pp, data, *data_size);
            //if(0 != *data_size) data_size = 0; 
        } 
        //DEBUG:
        fprintf(stdout, "in do_answer data %s\n", data);
        suc = do_parse_post_data(req, data);
        if(LADON_SUCCESS == suc){
            //do response for the successfully parsing user post data
            //
            //DEBUG:
            fprintf(stdout, "in do_answer parse user data done, and form response\n");
            MHD_destroy_post_processor(req->pp);
            *data_size = 0;
            req->pp = NULL;
            *ptr = req->pp;
            method = MHD_HTTP_METHOD_GET; 
        }else{
            //do response for the failure of parsing user post data 
            //
        }
    }
    
    if(NULL == *ptr){
        const char* resp_data = "<html><title>MHD</title><body>Fuck yeah!</body></html>";
        MHD_Response* resp = MHD_create_response_from_buffer(strlen(resp_data), (void*)resp_data, MHD_RESPMEM_PERSISTENT); 
        suc = MHD_queue_response(conn, MHD_HTTP_OK, resp);
        fprintf(stdout, "in do_answer suc: %d\n", suc);
        MHD_destroy_response(resp);
    }

    /*
    if(LADON_SUCCESS == suc
            && (strncmp(method, MHD_HTTP_METHOD_GET, strlen(method)) 
            || strncmp(method, MHD_HTTP_METHOD_HEAD, strlen(method)))){ 
        do_echo(conn);
    }else suc = handle_error();
    */
    return LADON_SUCCESS;
} 

static void request_complete(void* cls, MHD_Connection* conn, void** con_cls, MHD_RequestTerminationCode toe){
    fprintf(stdout, "in request_complete\n");
    int suc = LADON_SUCCESS;
    Request* req = (Request*)*con_cls;
    //handle resource deleting
    delete req;
    req = NULL;
}

int main(){
    //init daemon for mhd 
    //if request comes 
    //    post data:   job id
    //                 ob connect info: host, ip, account, password
    //                 tempory table name
    //                 suicide flag 
    
    //init connection object
    //

    int port = 8888; 
    MHD_Daemon* data_reboot = MHD_start_daemon(MHD_USE_DEBUG, port, NULL, NULL, &do_answer, NULL, 
            MHD_OPTION_CONNECTION_TIMEOUT, (unsigned int)15, MHD_OPTION_NOTIFY_COMPLETED, &request_complete, NULL ,MHD_OPTION_END);
    while(true){
        MHD_run(data_reboot); 
    }
    MHD_stop_daemon(data_reboot);
    return 0;
}
