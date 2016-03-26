/*
Autores:
    Kevin Hernández
    Estefany Salas
*/

#include <iostream>
#include <string.h>
#include <stdio.h>
#include "memcompa.h"
using namespace std;
int main(int argc, char *argv[]){
    string room_name;
    const string room = "ek";
    cout << "Ingrese el nombre de la sala a la que desea ingresar"<<endl;
    cin  >> room_name;
    if(room == room_name)
        cout << "You're in" <<endl;
}
