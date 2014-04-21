/*
 * test main
 *
 */

#define LOG_TAG "testMain"
#include <utils/Log.h>

#include <getopt.h>
#include <stdlib.h>
#include <stdio.h>
#include <fcntl.h>
#include <string.h>
#include <unistd.h>
#include <sys/time.h>
#include <string.h>

#include "testmodule.h"
 

int main(int argc, char *argv[])
{
    ALOGV("[%s] enter.\n", __FUNCTION__);
    char input[32] = {0};
    
    Test *pTest = new Test;
    
    pTest->foo();
    
    while(true) {
    
        ALOGV("[%s] please input command: \n", __FUNCTION__);
        gets(input);
        
        if(!strcmp(input , "exit")) {
            break;   
        }
        
        if(!strcmp(input , "readtest")) {
            pTest->readTest();
        }
        else if(!strcmp(input , "writetest")) {
            printf("please input str\n");
            char inputstr[32] = {0};
            gets(inputstr);
            pTest->writeTest(inputstr);
        } 
    }
    
    delete pTest;
    
    ALOGV("[%s] Exit.\n", __FUNCTION__);
    
    return 0 ;   
}            
