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
    std::mutex m;
public:
    Registro();
    void addDato(int add);
    void replaceDatoMin(int reemplazo);
    void replaceDatoMax(int reemplazo);
    void addPartes(int add);
    void reset();
    void printDato();
    void printDiv();
    ~Registro();
};



#endif //_REGISTRO_H
