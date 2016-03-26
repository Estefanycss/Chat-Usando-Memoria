#ifndef  MEMCOMPA_H
#define  MEMCOMPA_H
#include <string>
#include <iostream>
#include <stdio.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/shm.h>
using namespace std;
class memcompa {
  public:
    memcompa(string room_name);
    void agregar_msg(string message);
    int strToAsciiInt(string var);
  private:
    int var_comp;
    string client_name;
    string *p;
};

#endif
