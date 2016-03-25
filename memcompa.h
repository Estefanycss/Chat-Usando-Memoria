#ifndef  MEMCOMPA_H
#define  MEMCOMPA_H
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/shm.h>

class memcompa {
  public: 
    int agregar_msg(char *msg);
    void modificar_msg(int clave, char valor[100]);
    char* consultar_msg(int clave);
    void destruir_msg(int clave);
};

#endif
