#ifndef  MEMCOMPA_H
#define  MEMCOMPA_H
#include <string>
#include <string.h>
#include <iostream>
#include <stdio.h>
//Hilos
#ifdef __linux__
  #include <pthread.h>
  #include <unistd.h>
  #include <stdlib.h>
#endif
//Manejo de memoria
#ifdef __linux__
  #include <sys/types.h>
  #include <sys/ipc.h>
  #include <sys/shm.h>
#elif _WIN32
  #include <windows.h>
  #include <conio.h>
  #include <stdlib.h>
  #include <errno.h>
  #include <tchar.h>
  #include <strsafe.h>
#endif

#include "graphicInterface.h"

#define CLAVE 20000000000
#define msg_long 500
using namespace std;
class memcompa {
  public:
    memcompa(graphicInterface *ui);
    void agregar_msg(const char * message);

    #if __linux__
      void *leerMsg(void);
      void *escribirMsg(void);
      static void *threadedleerMsg(void *context);
      static void *threadedAgregar_msg(void *context);
      void instanciaHilo(pthread_t *hilo, void *(*funcion_hilo)(void *));
      void iniciarHilo(pthread_t hilo);
    #elif _WIN32
      DWORD leerMsg(void);
      DWORD escribirMsg(void);
      static DWORD WINAPI threadedleerMsg(void* context);
      static DWORD WINAPI threadedAgregar_msg(void* context);
      void instanciaHilo(HANDLE *hilo, void *(*funcion_hilo)(void *));
      void iniciarHilo(HANDLE hilo);
      bool validate(HANDLE manejador);
    #endif
    int strToAsciiInt(string var);
    static void dormir(float tiempo);
  private:
    #if __linux__
      char * p;
      int var_comp;
    #elif _WIN32
      LPCTSTR p;
      TCHAR clave[100], valor[msg_long];
      HANDLE var_comp;
    #endif
    graphicInterface *ui;
    char message_value[msg_long];
};

#endif
