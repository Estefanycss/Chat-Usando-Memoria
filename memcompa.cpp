#include "memcompa.h"

memcompa::memcompa(graphicInterface *ui){
  #ifdef __linux__
    pthread_t leer;
    pthread_t escribir;
  #elif _WIN32
  	/* Guardar colores de la consola*/
	  hConsola = GetStdHandle(STD_OUTPUT_HANDLE);
    GetConsoleScreenBufferInfo(hConsola, &consolaInfo);
    COLOR_NORMAL_W = consolaInfo.wAttributes;
    HANDLE control;
  #endif
  var_comp = shmget((key_t)  strToAsciiInt(ui->loadIn()), sizeof(message_value), IPC_CREAT|0666);
  if(var_comp > 0){
    this->ui = ui;

    cin.get();
    //instanciaHilo(&control, memcompa::threadedleerMsg);
    pthread_create(&leer, NULL, memcompa::threadedleerMsg, this);
    pthread_create(&escribir, NULL, memcompa::threadedAgregar_msg, this);
    pthread_join (escribir, NULL);
    pthread_join (leer, NULL);

    //iniciarHilo(control);
  }else
    exit(-1);
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
  p = static_cast<char *>(shmat(var_comp,NULL,0));
  strcpy(p, message);
  shmdt(p);
}
void *memcompa::escribirMsg(void){
  string var;
  while(true){
    var = this->ui->getUserName() + ": " + string(this->ui->loadChatMInterface());
    agregar_msg(var.c_str());
    dormir(1);
  }
}
void *memcompa::leerMsg(void){
  while(true){
    char * p = static_cast<char *>(shmat(var_comp,NULL,0));
    strcpy(message_value, p);
    shmdt(p);
    if(strcmp(message_value, ui->getLastMessage().c_str()))
      ui->addNewMessage(string(message_value));
  }
}
#if __linux__
  void *memcompa::threadedleerMsg(void *context){
#elif _WIN32
  DWORD WINAPI *memcompa::threadedleerMsg(LPVOID n_pr){
  int *n_pro = (int *)n_pr;
#endif
  return (static_cast<memcompa *>(context))->leerMsg();
}

#if __linux__
  void *memcompa::threadedAgregar_msg(void *context){
#elif _WIN32
  DWORD WINAPI *memcompa::threadedAgregar_msg(LPVOID n_pr){
  int *n_pro = (int *)n_pr;
#endif
  return (static_cast<memcompa *>(context))->escribirMsg();
}

#ifdef __linux__
void memcompa::instanciaHilo(pthread_t *hilo, void *(*funcion_hilo)(void *)){
#elif _WIN32
void memcompa::instanciaHilo(HANDLE *hilo, void *(*funcion_hilo)(void *)){
  DWORD hiloId;
  HANDLE  mhilo = CreateThread (
  NULL,       // Atributo de seguridad: Usar el de la thread actual
  0,          // Tamaño del stack. Usar el tamaño por defecto
  *funcion_hilo, // Función inicial de la thread
  (LPVOID) parametro,    // Datos a pasar a la thread
  0,          // Flags de creación
  &hiloId
  );
  *hilo = mhilo;
#endif
  #ifdef __linux__
    if (pthread_create(hilo, NULL, funcion_hilo, NULL)){
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

void memcompa::dormir(float tiempo){
  #ifdef __linux__
    sleep(tiempo);
  #elif _WIN32
    Sleep(tiempo*1000);
  #endif
}
