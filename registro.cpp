#include "registro.h"
#include <iostream>
#include <fstream>
#include <string.h>
#include <arpa/inet.h>
#include <ios>
#include <mutex>

Registro::Registro() 
: dato(0), partes(0), primer_num_flag(true){
}


void Registro::addDato(int add){
    std::lock_guard<std::mutex> lock(m);
    this->dato += add;
}

void Registro::replaceDatoMin(int reemplazo){
    std::lock_guard<std::mutex> lock(m);
    if (primer_num_flag){
        this->dato = reemplazo;
        primer_num_flag = false;
    } else{
        if (this->dato > reemplazo)
        this->dato = reemplazo;
    }
}

void Registro::replaceDatoMax(int reemplazo){
    std::lock_guard<std::mutex> lock(m);
    if (this->dato < reemplazo)
    this->dato = reemplazo;
}


void Registro::addPartes(int add){
    std::lock_guard<std::mutex> lock(m);
    this->partes += add;
}

void Registro::printDato(){
    printf("%d\n", this->dato);
}

void Registro::reset(){
    dato = 0;
    partes = 0;
    primer_num_flag = true;
}

void Registro::printDiv(){
    printf("%d/%d\n", this->dato, this->partes);
}

Registro::~Registro()
{
}
