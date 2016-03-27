#ifndef  MEMCOMPA_H
#define  MEMCOMPA_H
#include <string>
#include <string.h>
#include <iostream>
#include <stdio.h>
//Hilos
#ifdef __linux__
  #include <pthread.h>
  #include <semaphore.h>
  #include <unistd.h>
  #include <stdlib.h>
#elif _WIN32
  #include <conio.h>
  #include <windows.h>
  #include <tchar.h>
  #include <strsafe.h>
#endif
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
    void *leerMsg(void);
    void *escribirMsg(void);
    #if __linux__
      static void *threadedleerMsg(void *context);
      static void *threadedAgregar_msg(void *context);
      void instanciaHilo(pthread_t *hilo, void *(*funcion_hilo)(void *));
      void iniciarHilo(pthread_t hilo);
    #elif _WIN32
      DWORD WINAPI *threadedleerMsg(LPVOID n_pr);
      DWORD WINAPI *threadedAgregar_msg(LPVOID n_pr);
      void instanciaHilo(HANDLE *hilo, void *(*funcion_hilo)(void *));
      void iniciarHilo(HANDLE hilo);
    #endif
    int strToAsciiInt(string var);
    static void dormir(float tiempo);
  private:
    int var_comp;
    char * p;
    graphicInterface *ui;

    char message_value[500];
};

#endif
