#ifndef  GRAPHICINTERFACE_H
#define  GRAPHICINTERFACE_H
#include <string>
#include <iostream>
#include <stdio.h>
#include <vector>
#ifdef _WIN32
  #include <conio.h>
  #include <windows.h>
  #include <tchar.h>
  #include <strsafe.h>
#endif
#define COLOR_ROJO            "\x1b[31m"
#define COLOR_NORMAL          "\x1b[0m"
#define COLOR_VERDE           "\x1b[32m"
#define COLOR_AZUL            "\x1b[34m"
#define COLOR_NOTIFICACION    "\x1b[47m"
using namespace std;
class graphicInterface{
  public:
    string loadIn();
    string getLastMessage();
    void addNewMessage(string message);
    void loadChatInterface();
    void crearRecuadro();
  private:
    void gotoxy(int x, int y);
    vector<string> messages;
};

#endif
