#include "graphicInterface.h"

string graphicInterface::loadIn(){
  string room_name = "EK";
  cout << "Welcome to the coolest chat on earth" << endl << endl;
  cout << "Write room name: ";
  cin >> room_name;
  return room_name;
}

void graphicInterface::gotoxy(int x, int y){
#ifdef __linux__
  printf (" \033[%d;%dH", x, y);
#elif _WIN32
  COORD coord;
  coord.X = x;
  coord.Y = y;
  SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
#endif
}
