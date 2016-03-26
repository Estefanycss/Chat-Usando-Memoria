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
    string room_name;
    cout << "Ingrese el nombre de la sala a la que desea ingresar"<<endl;
    cin  >> room_name;
}
