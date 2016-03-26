#include "memcompa.h"

memcompa::memcompa(string room_name){
  string message;
  std::cout << "Received: " << room_name << ". Created key: " << strToAsciiInt(room_name)  << std::endl;
  var_comp = shmget((key_t) strToAsciiInt(room_name), sizeof(int), IPC_CREAT|0666);
  cout << endl << "Write your name: ";
  cin >> client_name;
  //system('clr');
  cout << "Chat room " <<room_name <<endl << endl;
  cin >> message;
  agregar_msg(message);
}
int memcompa::strToAsciiInt(string var){
  int sum = 0;
    for (int i = 0; i < var.length(); i++){
        char x = var.at(i);
        sum += int(x);
    }
    return sum;
}
void memcompa::agregar_msg(string message){
    p = (string *)shmat(var_comp,NULL,0);  //conexion
    cout<<"connect  "<<p<<endl;
    *p = message;  //<<-------AQUI
    cout << *p <<endl;
    cout<< "casting a char" <<endl;
    shmdt((char *) p->c_str()); //desconectar
    cout<<"disconnect";
    //NOW LETS SEE IF THIS WORK
    p = (string *)shmat(var_comp,NULL,0);
    message = *p;
    shmdt((char *)p);
    cout << "This is in the memory: " << message;
}
