/*
Autores:
    Kevin Hernández
    Estefany Salas
*/

#include <iostream>
#include <stdio.h>
#include "memcompa.h"
#include "graphicInterface.h"
#include <string.h>
using namespace std;
int main(int argc, char *argv[]){
    graphicInterface *ui;
    ui = new graphicInterface;
    memcompa mc(ui);
}
