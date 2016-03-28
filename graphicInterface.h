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
#ifdef __linux__
  #define COLOR_ROJO            "\x1b[31m"
  #define COLOR_NORMAL          "\x1b[0m"
  #define COLOR_VERDE           "\x1b[32m"
  #define COLOR_AZUL            "\x1b[34m"
  #define COLOR_NOTIFICACION    "\x1b[47m"
#elif _WIN32
  #define COLOR_ROJO            ""
  #define COLOR_NORMAL          ""
  #define COLOR_VERDE           ""
  #define COLOR_AZUL            ""
  #define COLOR_NOTIFICACION    ""
#endif
using namespace std;
class graphicInterface{
  public:
    graphicInterface();
    string loadIn();
    string getLastMessage();
    string getUserName();
    void addNewMessage(string message);
    char * loadChatMInterface();
    void loadChatInterface();
    void crearRecuadro();
    void clear();
  private:
    void gotoxy(int x, int y);
    string client_name;
    string room_name;
    vector<string> messages;
    #ifdef _WIN32
      HANDLE hConsola;
      CONSOLE_SCREEN_BUFFER_INFO consolaInfo;
      WORD COLOR_NORMAL_W;
    #endif
};

#endif
