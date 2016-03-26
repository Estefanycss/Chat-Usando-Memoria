#include "memcompa.h"

memcompa::memcompa(graphicInterface *ui){
  string message;
  string room_name = ui->loadIn();
  //std::cout << "Received: " << room_name << ". Created key: " << strToAsciiInt(room_name)  << std::endl;
  var_comp = shmget((key_t) strToAsciiInt(room_name), sizeof(message_value), IPC_CREAT|0666);
  cout << ui->getUserName() << " write a message: ";
  cin.get();
  cin.getline(message_value, 100);
  agregar_msg(message_value);
  cout << "Press enter";
  cin.get();
  cout << "\033[H\033[J";
  ui->loadChatInterface();
}
int memcompa::strToAsciiInt(string var){
  int sum = 0;
    for (int i = 0; i < var.length(); i++){
        char x = var.at(i);
        sum += int(x);
    }
    return CLAVE + sum;
}
void memcompa::agregar_msg(char * message){
  p = static_cast<char *>(shmat(var_comp,NULL,0));
  strcpy(p, message);
  cout << "Sending: " << message << endl;
  shmdt(p);

  p = static_cast<char *>(shmat(var_comp,NULL,0));

  strcpy(message, p);
  //valor = *p;
  shmdt(p);
  cout << "Receiving: " << message << endl;
}
