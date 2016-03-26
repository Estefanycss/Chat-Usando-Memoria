#include "memcompa.h"

memcompa::memcompa(graphicInterface *ui){
  string message;
  string room_name = ui->loadIn();
  var_comp = shmget((key_t) strToAsciiInt(room_name), sizeof(message_value), IPC_CREAT|0666);
  if(var_comp > 0){
    this->ui = ui;
    //Por motivos de prueba:
    string var;
    cin.get();
    while(true){
        var = this->ui->getUserName() + ": " + string(this->ui->loadChatMInterface());
        agregar_msg(var.c_str());
        //agregar_msg(this->ui->loadChatMInterface());
    }
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
  leerMsg();
}
void memcompa::leerMsg(){
  p = static_cast<char *>(shmat(var_comp,NULL,0));
  strcpy(message_value, p);
  shmdt(p);
  if(message_value)
    ui->addNewMessage(string(message_value));
}
