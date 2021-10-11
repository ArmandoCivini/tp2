#ifndef _REGISTRO_H
#define _REGISTRO_H

#include <iostream>
#include <fstream>
#include <string.h>
#include <arpa/inet.h>
#include <ios>
#include <mutex>


class Registro
{
private:
    int dato;
    int partes;
    bool primer_num_flag;
    std::mutex* m;
public:
    Registro();
    void reset();
    void setMutex(std::mutex *mu);
    void addDato(int add);
    void replaceDatoMin(int reemplazo);
    void replaceDatoMax(int reemplazo);
    void addPartes(int add);
    void printDato();
    void printDiv();
    ~Registro();
};

Registro::Registro(){
    dato = 0;
    partes = 0;
    primer_num_flag = true;
}

void Registro::reset(){
    this->dato = 0;
    this->partes = 0;
}

void Registro::setMutex(std::mutex *mu){
    this->m = mu;
}

void Registro::addDato(int add){
    m->lock();
    this->dato += add;
    m->unlock();
}

void Registro::replaceDatoMin(int reemplazo){
    m->lock();
    if (primer_num_flag){
        this->dato = reemplazo;
        primer_num_flag = false;
    } else{
        if (this->dato > reemplazo)
        this->dato = reemplazo;
    }
    m->unlock();
}

void Registro::replaceDatoMax(int reemplazo){
    m->lock();
    if (this->dato < reemplazo)
    this->dato = reemplazo;
    m->unlock();
}


void Registro::addPartes(int add){
    m->lock();
    this->partes += add;
    m->unlock();
}

void Registro::printDato(){
    std::cout <<  this->dato << std::endl;
}

void Registro::printDiv(){
    std::cout <<  this->dato << "/" 
    << this->partes << std::endl;
}

Registro::~Registro()
{
}


#endif //_REGISTRO_H
