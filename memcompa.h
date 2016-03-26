#ifndef  MEMCOMPA_H
#define  MEMCOMPA_H
#include <string>
#include <string.h>
#include <iostream>
#include <stdio.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#define CLAVE 2000000000
using namespace std;
class memcompa {
  public:
    memcompa(string room_name);
    void agregar_msg(char * message);
    int strToAsciiInt(string var);
  private:
    int var_comp;
    char * p;
    char message_value[100];
};

#endif
