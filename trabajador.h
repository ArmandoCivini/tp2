#ifndef _TRABAJADOR_H
#define _TRABAJADOR_H

#include "colaindxsegura.h"
#include "registro.h"
#include "lector.h"
#include "procesador.h"
#include <iostream>
#include <fstream>
#include <string.h>
#include <arpa/inet.h>
#include <mutex>
#include <algorithm>
#include <vector>
#include <string>

class Trabajador
{
private:
    int numero_de_columnas;
    ColaIndxSegura& cola;
    Registro& registro;
    std::string archivo;
    Lector lector;
    void setCalc(IndexArchivo index, std::vector<int>& numeros);
public:
    Trabajador
    (int numero_de_columnas
    , ColaIndxSegura& cola, Registro& reg, const std::string& in_file);
    Trabajador(Trabajador&& Trabajador) :
            numero_de_columnas(Trabajador.numero_de_columnas),
            cola(Trabajador.cola),
            registro(Trabajador.registro),
            archivo(Trabajador.archivo),
            lector(Trabajador.archivo){ }
    void trabajar();
    ~Trabajador();
};


#endif //_Trabajador_H
