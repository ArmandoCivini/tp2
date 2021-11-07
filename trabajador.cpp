#include "trabajador.h"
#include <string.h>
#include <mutex>
#include <algorithm>
#include <vector>
#include <string>

Trabajador::Trabajador
(int numero_de_columnas
, ColaIndxSegura& cola, Registro& reg, const std::string& in_archivo)
: numero_de_columnas(numero_de_columnas), cola(cola), 
registro(reg), archivo(in_archivo), lector(archivo){
}

void Trabajador::setCalc(IndexArchivo index, std::vector<int>& numeros){
    const std::string& operacion = index.op;
    if (operacion=="sum"){
        ProcesadorSum(index, numeros, numero_de_columnas, registro);
    } else if (operacion=="mean"){
        ProcesadorMean(index, numeros, numero_de_columnas, registro);
    } else if (operacion=="max"){
        ProcesadorMax(index, numeros, numero_de_columnas, registro);
    } else{
        ProcesadorMin(index, numeros, numero_de_columnas, registro);
    }
}

void Trabajador::trabajar(){
    bool termino=false;
    IndexArchivo index = cola.pop(&termino);
    while (!termino){
        std::vector<int> numeros = this->lector.readIndex(index);
        setCalc(index, numeros);
        index = cola.pop(&termino);
    }
}

Trabajador::~Trabajador(){
}
