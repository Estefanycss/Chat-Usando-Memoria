/*
Autores:
    Kevin Hernández
    Estefany Salas
*/

#include <iostream>
#include <stdio.h>
#include "memcompa.h"
#include "graphicInterface.h"
using namespace std;
int main(int argc, char *argv[]){
    graphicInterface ui;
    memcompa mc(ui.loadIn());
    //cout << "\033[H\033[J";
    //ui.loadChatInterface();

}
