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
    int agregar_msg(char *msg);
    void modificar_msg(int clave, char valor[100]);
    char* consultar_msg(int clave);
    void destruir_msg(int clave);
    int strToAsciiInt(string var);
  private:
    int var_comp;
};

#endif
