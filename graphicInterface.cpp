#include "graphicInterface.h"
graphicInterface::graphicInterface(){
  #ifdef _WIN32
    hConsola = GetStdHandle(STD_OUTPUT_HANDLE);
    GetConsoleScreenBufferInfo(hConsola, &consolaInfo);
    COLOR_NORMAL_W = consolaInfo.wAttributes;
  #endif
}
string graphicInterface::loadIn(){
  string room_name;
  clear();
  crearRecuadro();
  gotoxy(2, 5);
  cout << "Welcome to the coolest chat on earth" << endl << endl;
  cout << "\tWrite room name: ";
  cin >> room_name;
  cout << endl << "\tWrite your name: ";
  cin >> client_name;
  this->room_name = room_name;
  clear();
  loadChatInterface();
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
  coord.X = y;
  coord.Y = x;
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
  int x = 26, y = 7;
  clear();
  crearRecuadro();
  gotoxy(0, 2);
  cout << COLOR_ROJO << client_name <<", estas chateando en la sala: " << room_name << endl;
  gotoxy(2, 2);
  cout << COLOR_ROJO << "[" <<messages.size() << " mensajes recibidos]" << endl;
  for (int i = messages.size() - 1; i >= 0 && x > 2; i--) {
    #ifdef __linux__
      y = (messages.at(i).substr(0, messages.at(i).find(":")) == getUserName())?7:(75 - messages.at(i).length());
    #elif _WIN32
      y = (messages.at(i).substr(0, messages.at(i).find(":")) == getUserName())?7:(55 - messages.at(i).length());
    #endif
     gotoxy(x, y);
     x -= 2;
     cout << COLOR_NORMAL << messages.at(i);
  }
  #ifdef __linux__
    gotoxy(30, 2);
  #elif _WIN32
    gotoxy(27, 2);
  #endif
  cout << COLOR_AZUL << "Mensaje" << endl << "\t";
}
char * graphicInterface::loadChatMInterface(){
  static char mess[500];
  #ifdef __linux__
    gotoxy(30, 2);
  #elif _WIN32
    gotoxy(27, 2);
  #endif
  cout << COLOR_AZUL << "Mensaje" << endl << "\t";
  cin.getline(mess, 500);
  return mess;
}

void graphicInterface::crearRecuadro(){
  int index;
  int tam_largo = 30;
  int tam_ancho;
  int x, y;
  x = 0; y = 0;
  #ifdef __linux__
    int tam_ancho = 80;
    cout << COLOR_VERDE;
    gotoxy(x, y);
    for(index = 0; index < tam_ancho; index++){
      if(!index)
        cout << "┌";
      else
        cout << "─";
    }
      cout << "┐";
    x = 2;
    for(index = 0; index < tam_largo; index++){
      gotoxy(x, y);
      cout << "│";
      x++;
    }
    x = tam_largo + 2;
    y = 0;
    gotoxy(x, y);
    for(index = 0; index < tam_ancho; index++){
      if(!index)
        cout << "└";
        else
          cout << "─";
        }
    x = 2;
    y = tam_ancho + 1;
    for(index = 0; index < tam_largo; index++){
      gotoxy(x, y);
      cout << "│";
      x++;
    }
    gotoxy(x, y);
    cout << "┘";
    cout << COLOR_NORMAL;
  #elif _WIN32
    tam_ancho = 70;
    SetConsoleTextAttribute(hConsola, FOREGROUND_GREEN);
    cout << (char)219;
    gotoxy(x, y + 1);
    for(index = 0; index < tam_ancho; index++)
      cout << "-";
    cout << (char)219;
    x = 1;
    for(index = 0; index < tam_largo; index++){
      gotoxy(x, y);
      cout << "|";
      x++;
    }
    gotoxy(x, y);
    cout << (char)219;
    x = tam_largo + 1;
    y = 1;
    gotoxy(x, y);
    for(index = 0; index < tam_ancho + 1; index++)
      cout << "-";
    x = 1;
    y = tam_ancho + 1;
    for(index = 0; index < tam_largo; index++){
      gotoxy(x, y);
      cout << "|";
      x++;
    }
    gotoxy(x, y);
    cout << (char)219;
    SetConsoleTextAttribute(hConsola, COLOR_NORMAL_W);
  #endif
}

void graphicInterface::clear(){
  #ifdef __linux__
     cout << "\033[H\033[J";
  #elif _WIN32
     system("cls");
  #endif
}
