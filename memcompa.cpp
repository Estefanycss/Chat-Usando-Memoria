#include "memcompa.h"

memcompa::memcompa(string room_name){
  std::cout << "Received: " << room_name << ". Created key: " << strToAsciiInt(room_name)  << std::endl;
  var_comp = shmget((key_t) strToAsciiInt(room_name), sizeof(int), IPC_CREAT|0666);
}
int memcompa::strToAsciiInt(string var){
  int sum = 0;
    for (int i = 0; i < var.length(); i++){
        char x = var.at(i);
        sum += int(x);
    }
    return sum;
}
int memcompa::agregar_msg(char *msg){

}

void memcompa::modificar_msg(int clave, char valor[100]){

}

char* memcompa::consultar_msg(int clave){

}

void memcompa::destruir_msg(int clave){

}
