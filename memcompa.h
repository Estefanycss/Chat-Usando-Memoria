#ifndef  MEMCOMPA_H
#define  MEMCOMPA_H
#include <string>
#include <string.h>
#include <iostream>
#include <stdio.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include "graphicInterface.h"
#define CLAVE 20000000000
using namespace std;
class memcompa {
  public:
    memcompa(graphicInterface *ui);
    void agregar_msg(const char * message);
    void leerMsg();
    int strToAsciiInt(string var);
  private:
    int var_comp;
    char * p;
    graphicInterface *ui;
    char message_value[500];
};

#endif
