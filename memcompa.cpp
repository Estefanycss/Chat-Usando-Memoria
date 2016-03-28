#include "memcompa.h"

memcompa::memcompa(graphicInterface *ui){
  #ifdef __linux__
    pthread_t leer;
    pthread_t escribir;
  #elif _WIN32
	HANDLE leer;
    HANDLE escribir;
  #endif
  this->ui = ui;
  #ifdef __linux__
    var_comp = shmget((key_t)  strToAsciiInt(ui->loadIn()), sizeof(message_value), IPC_CREAT|0666);
    if(var_comp < 0)
	    exit(-1);
      instanciaHilo(&leer, memcompa::threadedleerMsg);
      instanciaHilo(&escribir, memcompa::threadedAgregar_msg);

  #elif _WIN32
    DWORD idleer, idescribir;
  	string room = "Local\\";
  	room += ui->loadIn();
    StringCchCopy(clave, room.length() + 1, room.c_str());
    leer     = CreateThread(NULL, 0, memcompa::threadedleerMsg,     (void*) this, 0, &idleer);
    escribir = CreateThread(NULL, 0, memcompa::threadedAgregar_msg, (void*) this, 0, &idescribir);
  #endif
  cin.get();
  iniciarHilo(escribir);
  iniciarHilo(leer);
}
int memcompa::strToAsciiInt(string var){
  int sum = 0;
    for (int i = 0; i < var.length(); i++){
        char x = var.at(i);
        sum += int(x);
    }
    return CLAVE + sum;
}
void memcompa::agregar_msg(const char * message){
  #ifdef __linux__
    p = static_cast<char *>(shmat(var_comp,NULL,0));
    strcpy(p, message);
    shmdt(p);
  #elif _WIN32
    HANDLE var_comp = CreateFileMapping( INVALID_HANDLE_VALUE, // Especificacion de página
    NULL, // Atributos de seguridad
    PAGE_READWRITE, // Permiso de escritura y lectura
    0,
    sizeof(int), // tamaño máximo
    clave
    );
    if(validate(var_comp)){
	    p = (LPTSTR) MapViewOfFile(var_comp, FILE_MAP_ALL_ACCESS, 0, 0, sizeof(int));
	    CopyMemory((PVOID) p, message, sizeof(TCHAR) * msg_long);
	    UnmapViewOfFile(p);
    }
  #endif
}
#if __linux__
  void *memcompa::escribirMsg(void){
#elif _WIN32
  DWORD memcompa::escribirMsg(void){
#endif
  string var;
  while(true){
    var = this->ui->getUserName() + ": " + string(this->ui->loadChatMInterface());
    if(var.find("exit") == string::npos)
    	agregar_msg(var.c_str());
    else
    	exit(0);
    dormir(1);
  }
}
#if __linux__
  void *memcompa::leerMsg(void){
#elif _WIN32
  DWORD memcompa::leerMsg(void){
#endif
  while(true){
    #ifdef __linux__
      char * p = static_cast<char *>(shmat(var_comp,NULL,0));
      strcpy(message_value, p);
      shmdt(p);
      if(strcmp(message_value, ui->getLastMessage().c_str()))
        ui->addNewMessage(string(message_value));
    #elif _WIN32
      HANDLE var_comp = OpenFileMapping( FILE_MAP_ALL_ACCESS, FALSE, clave);
      if(validate(var_comp)){
        p = (LPTSTR) MapViewOfFile(var_comp, FILE_MAP_READ, 0, 0, sizeof(TCHAR) * msg_long);
        if(strcmp(p, ui->getLastMessage().c_str()))
          ui->addNewMessage(string(p));
        UnmapViewOfFile(p);
      }
    #endif
  }
}
//Elegante: 8|
#if __linux__
  void *memcompa::threadedleerMsg(void *context){
#elif _WIN32
  DWORD WINAPI memcompa::threadedleerMsg(void* context){
#endif
  return (static_cast<memcompa *>(context))->leerMsg();
}

#if __linux__
  void *memcompa::threadedAgregar_msg(void *context){
#elif _WIN32
  DWORD WINAPI memcompa::threadedAgregar_msg(void* context){
#endif
  return (static_cast<memcompa *>(context))->escribirMsg();
}


#ifdef __linux__
void memcompa::instanciaHilo(pthread_t *hilo, void *(*funcion_hilo)(void *)){
#elif _WIN32
void memcompa::instanciaHilo(HANDLE *hilo, void *(*funcion_hilo)(void *)){
  DWORD hiloId;
  /*HANDLE  mhilo = CreateThread (
  NULL,       // Atributo de seguridad: Usar el de la thread actual
  0,          // Tamaño del stack. Usar el tamaño por defecto
  funcion_hilo, // Función inicial de la thread
  (void *) this,    // Datos a pasar a la thread
  0,          // Flags de creación
  &hiloId
  );
  *hilo = mhilo;*/
#endif
  #ifdef __linux__
    if (pthread_create(hilo, NULL, funcion_hilo, this)){
  #elif _WIN32
    if(hilo == NULL){
  #endif
      cout << "Error al crear el hilo.";
      abort();
    }
}

#ifdef __linux__
  void memcompa::iniciarHilo(pthread_t hilo){
#elif _WIN32
  void memcompa::iniciarHilo(HANDLE hilo){
#endif
    #ifdef __linux__
      if ( pthread_join (hilo, NULL) ) {
    #elif _WIN32
      if (WaitForSingleObject(hilo, INFINITE) == WAIT_FAILED){
    #endif
        cout << "Error al iniciar el hilo.";
        abort();
      }
}
#if _WIN32
  bool memcompa::validate(HANDLE manejador){
   if ( manejador == NULL){
   //_tprintf(TEXT("Could not create file mapping object (%d).\n"),GetLastError());
   return false;
   }
   return true;
  }
#endif

void memcompa::dormir(float tiempo){
  #ifdef __linux__
    sleep(tiempo);
  #elif _WIN32
    Sleep(tiempo*1000);
  #endif
}
