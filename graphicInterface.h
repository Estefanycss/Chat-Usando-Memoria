#ifndef  GRAPHICINTERFACE_H
#define  GRAPHICINTERFACE_H
#include <string>
#include <iostream>
#include <stdio.h>
#ifdef _WIN32
  #include <conio.h>
  #include <windows.h>
  #include <tchar.h>
  #include <strsafe.h>
#endif
using namespace std;
class graphicInterface{
  public:
    string loadIn();
  private:
    void gotoxy(int x, int y);
};

#endif
