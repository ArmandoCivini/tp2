#include "procesador.h"
#include "colaindxsegura.h"
#include "registro.h"
#include <string.h>
#include <mutex>
#include <algorithm>
#include <vector>

Procesador::Procesador
(const IndexArchivo& index, int numero_de_columnas, std::vector<int>& numeros, Registro& registro)
: columna(index.columna), numero_de_columnas(numero_de_columnas)
, numeros(numeros), registro(registro){
}

void Procesador::calcular(){
    int resultado_actual = this->numeros[this->columna];
    for (std::size_t i = this->columna + this->numero_de_columnas; 
    i < numeros.size(); i+=numero_de_columnas) {
        resultado_actual = operacion(resultado_actual, this->numeros[i]);
    }
    registrar(resultado_actual);
}

Procesador::~Procesador(){
}

ProcesadorSum::ProcesadorSum
(const IndexArchivo& index, std::vector<int>& numeros, int numero_de_columnas, Registro& registro)
: Procesador(index, numero_de_columnas, numeros, registro){
    calcular();
}

int ProcesadorSum::operacion(int numero1, int numero2){
    return numero1 + numero2;
}

void ProcesadorSum::registrar(int resultado){
    this->registro.addDato(resultado);
}

ProcesadorSum::~ProcesadorSum(){
}


ProcesadorMean::ProcesadorMean
(const IndexArchivo& index, std::vector<int>& numeros, int numero_de_columnas, Registro& registro)
: Procesador(index, numero_de_columnas, numeros, registro){
    calcular();
}

int ProcesadorMean::operacion(int numero1, int numero2){
    return numero1 + numero2;
}

void ProcesadorMean::registrar(int resultado){
    this->registro.addDato(resultado);
    this->registro.addPartes(this->numeros.size()/this->numero_de_columnas);
}

ProcesadorMean::~ProcesadorMean(){
}

ProcesadorMin::ProcesadorMin
(const IndexArchivo& index, std::vector<int>& numeros, int numero_de_columnas, Registro& registro)
: Procesador(index, numero_de_columnas, numeros, registro){
    calcular();
}

int ProcesadorMin::operacion(int numero1, int numero2){
    return
    numero1 < numero2 ?
    numero1 : numero2;
}

void ProcesadorMin::registrar(int resultado){
    this->registro.replaceDatoMin(resultado);
}

ProcesadorMin::~ProcesadorMin(){
}
ProcesadorMax::ProcesadorMax
(const IndexArchivo& index, std::vector<int>& numeros, int numero_de_columnas, Registro& registro)
: Procesador(index, numero_de_columnas, numeros, registro){
    calcular();
}

int ProcesadorMax::operacion(int numero1, int numero2){
    return
    numero1 > numero2 ?
    numero1 : numero2;
}

void ProcesadorMax::registrar(int resultado){
    this->registro.replaceDatoMax(resultado);
}

ProcesadorMax::~ProcesadorMax(){
}
