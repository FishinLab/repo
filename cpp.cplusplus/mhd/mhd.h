#include <iostream>
#include <string.h>
#include <math.h>
//#include <mysql++.h>
#include <regex.h>
#include <stack>
#include <queue>
#include <stdlib.h>

extern "C" {
#include <lua.h>
#include <lualib.h>
#include <lauxlib.h>

#include <microhttpd.h> 
}

//#include "translator.h"
//#include "mhd.h"

using namespace std;

#define LADON_FAILURE 0
#define LADON_SUCCESS 1

struct MHD_Request{
    MHD_PostProcessor* proc;
    //MHD_Session* sess;
    const char* post_url;
};

