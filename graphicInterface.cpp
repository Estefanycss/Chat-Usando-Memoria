#include "graphicInterface.h"

string graphicInterface::loadIn(){
  string room_name;
  cout << "Welcome to the coolest chat on earth" << endl << endl;
  cout << "Write room name: ";
  cin >> room_name;
  cout << endl << "Write your name: ";
  cin >> client_name;
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
  crearRecuadro();
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
