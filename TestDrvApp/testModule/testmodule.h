/*
 * test module header file
 *
 */

#ifndef _TESTMODULE_H_
#define _TESTMODULE_H_
 
class Test {

public:
    Test();
    ~Test();
    
    void foo();
    
    int readTest();    
    int writeTest(const char *inputstr);
    
private:
//    int test_fd;    
    
};

#endif
                 


