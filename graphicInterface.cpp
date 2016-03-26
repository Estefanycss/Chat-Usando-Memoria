#include "graphicInterface.h"

string graphicInterface::loadIn(){
  string room_name;
  cout << "\033[H\033[J";
  crearRecuadro();
  gotoxy(2, 5);
  cout << "Welcome to the coolest chat on earth" << endl << endl;
  cout << "\tWrite room name: ";
  cin >> room_name;
  cout << endl << "\tWrite your name: ";
  cin >> client_name;
  this->room_name = room_name;
  return room_name;
}
string graphicInterface::getUserName(){
  return client_name;
}
void graphicInterface::gotoxy(int x, int y){
#ifdef __linux__
  cout << ("\033[" + std::to_string(x) + ";" + std::to_string(y) + "H");
#elif _WIN32
  COORD coord;
  coord.X = x;
  coord.Y = y;
  SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
#endif
}

string graphicInterface::getLastMessage(){
  if(!messages.empty())
    return messages.back();
  else
    return "";
}

void graphicInterface::addNewMessage(string message){
  messages.push_back(message);
  //Se agrega a la lista de mensajes y luego se cargan
  loadChatInterface();
}
void graphicInterface::loadChatInterface(){
  int x = 26, y = 2;
  cout << "\033[H\033[J";
  crearRecuadro();
  gotoxy(0, 2);
  cout << COLOR_ROJO << client_name <<" estas chateando en la sala: " << room_name;
  if(messages.size() > 0)
    for (int i = messages.size() - 1; i >= 0 && x > 2; i--) {
       y = (messages.at(i).find(getUserName()) != string::npos)?2:(80 - messages.at(i).length());
       gotoxy(x, y);
       x -= 2;
       cout << messages.at(i);
    }
}
char * graphicInterface::loadChatMInterface(){
  //Cargar mensajes anteriores
  static char mess[500];
  int x = 26, y = 2;
  cout << "\033[H\033[J";
  crearRecuadro();
  gotoxy(0, 2);
  cout << COLOR_ROJO << client_name <<" estas chateando en la sala: " << room_name;
  for (int i = messages.size() - 1; i >= 0 && x > 2; i--) {
     y = (messages.at(i).find(getUserName()) != string::npos)?2:(80 - messages.at(i).length());
     gotoxy(x, y);
     x -= 2;
     cout << COLOR_NORMAL << messages.at(i);
  }
  gotoxy(30, 2);
  cout << COLOR_ROJO << messages.size() << " mensajes recibidos";
  gotoxy(28, 2);
  cout << COLOR_AZUL << "Mensaje: ";
  cin.getline(mess, 500);
  crearRecuadro();
  return mess;
}
void graphicInterface::crearRecuadro(){
  int index;
  int tam_largo = 30;
  int tam_ancho = 80;
  int x, y;
  x = 0; y = 0;
  printf(COLOR_VERDE);
  gotoxy(x, y);
  for(index = 0; index < tam_ancho; index++){
    if(!index)
      printf ("┌");
    else
      printf ("─");
  }
    printf("┐");
  x = 2;
  for(index = 0; index < tam_largo; index++){
    gotoxy(x, y);
    printf ("│");
    x++;
  }
  x = tam_largo + 2;
  y = 0;
  gotoxy(x, y);
  for(index = 0; index < tam_ancho; index++){
    if(!index)
      printf ("└");
      else
        printf ("─");
      }
  x = 2;
  y = tam_ancho + 1;
  for(index = 0; index < tam_largo; index++){
    gotoxy(x, y);
    printf ("│");
    x++;
  }
  gotoxy(x, y);
  printf("┘");
  printf(COLOR_NORMAL);
}
