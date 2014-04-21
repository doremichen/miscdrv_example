/*
 * test module
 *
 */
#define LOG_NDEBUG 0 
#define LOG_TAG "testmodule"
#include <utils/Log.h>

#include <getopt.h>
#include <pthread.h>
#include <stdlib.h>
#include <stdio.h>
#include <fcntl.h>
#include <string.h>
#include <unistd.h>
#include <sys/time.h>
#include <semaphore.h>
#include <errno.h>

#include "testmodule.h"

#define TESTPATH "/dev/misc_drv_example" 

Test::Test()
{
  ALOGV("[%s] enter.\n", __FUNCTION__);
  
//  test_fd = open(TESTPATH, O_RDWR);
//  
//  if(test_fd < 0) {
//    ALOGE("[%s] Open %s fail. errno[%d]\n", __FUNCTION__, TESTPATH, errno); 
//  }  
        
}

Test::~Test()
{
  ALOGV("[%s] enter.\n", __FUNCTION__);
  
//  if(test_fd > 0) {
//    close(test_fd);  
//  }     
}                    

void Test::foo()
{
  ALOGV("[%s] enter.\n", __FUNCTION__);         
        
}   

int Test::readTest()
{
  ALOGV("[%s] enter.\n", __FUNCTION__);
  char buffer[32] = {0};
  int read_sz = 0;
  int ret = 1;
  int fd = -1;
  
  fd = open(TESTPATH, O_RDWR);
  
  if(fd < 0) {
    ALOGE("[%s] Open %s fail. errno[%d]\n", __FUNCTION__, TESTPATH, errno);
    goto END; 
  }     
  
  read_sz = read(fd, buffer, 32);
  
    if(!read_sz) {
       ALOGE("[%s] No data available.\n", __FUNCTION__);
       ret = 0;
       goto END;    
    }
  
    ALOGV("[%s] The actual read size is:%d.\n", __FUNCTION__, read_sz);
    ALOGV("[%s] The read content is:%s\n", __FUNCTION__, buffer);         

    close(fd);
    
  
//  if(test_fd > 0) {
//    
//    read_sz = read(test_fd, buffer, 200);
//    
//    if(!read_sz) {
//       ALOGE("[%s] No data available.\n", __FUNCTION__);
//       ret = 0;
//       goto END;    
//    }
//    
//    ALOGV("[%s] The actual read size is:%d.\n", __FUNCTION__, read_sz);
//    ALOGV("[%s] The read content is:%s\n", __FUNCTION__, buffer);    
//    
//  } 

END:  
  return ret;        
        
}  

int Test::writeTest(const char *inputstr)
{
  ALOGV("[%s] enter.\n", __FUNCTION__);
  char buffer[32] = {0};
  int req_sz = 32;
  int ret = 1;
  int fd = -1;
  
  fd = open(TESTPATH, O_RDWR);
  
  if(fd < 0) {
    ALOGE("[%s] Open %s fail. errno[%d]\n", __FUNCTION__, TESTPATH, errno);
    goto END; 
  }           
  
  strcpy(buffer, inputstr);
  
  
    if(!write(fd, buffer, req_sz)) {
       ALOGE("[%s] Device file Write Error!\n", __FUNCTION__);
       ret = 0;
       goto END;     
    }
    ALOGV("[%s] Write data successful.\n", __FUNCTION__);        

    close(fd);
  
  
//  if(test_fd > 0) {    
//    if(!write(test_fd, buffer, req_sz)) {
//       ALOGE("[%s] Device file Write Error!\n", __FUNCTION__);
//       ret = 0;
//       goto END;     
//    }
//    ALOGV("[%s] Write data successful.\n", __FUNCTION__);        
//  }   
END:  
  return ret;      
}       
