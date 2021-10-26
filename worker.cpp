#include "worker.h"
#include <iostream>
#include <fstream>
#include <string.h>
#include <arpa/inet.h>
#include <mutex>
#include <algorithm>
#include <vector>

int Worker::sumar(int numero1, int numero2){
    return numero1 + numero2;
}

int Worker::min(int numero1, int numero2){
    return
    numero1 < numero2 ?
    numero1 : numero2;
}

int Worker::max(int numero1, int numero2){
    return
    numero1 > numero2 ?
    numero1 : numero2;
}

Worker::Worker
(int numero_de_columnas
, SafeQueueString *cola, Registro *reg, char *in_file)
: numero_de_columnas(numero_de_columnas), cola(cola), 
registro(reg), pos_actual((columna* 2) + 2)
, replace_flag(false), max_flag(false)
, parser(in_file), columna(0), index(){
}



void Worker::process(int (*calculo)(int, int)){
    int resultado_actual = this->numeros[this->columna];
    for (std::size_t i = this->columna + this->numero_de_columnas;
     i < this->numeros.size(); i+=this->numero_de_columnas) {
        resultado_actual = calculo(resultado_actual, this->numeros[i]);
    }
    if (this->replace_flag){
        if (this->max_flag){
            this->registro->replaceDatoMax(resultado_actual);
        } else{
            this->registro->replaceDatoMin(resultado_actual);
        }
    } else{
        this->registro->addDato(resultado_actual);
    }
    this->registro->addPartes(this->numeros.size()/this->numero_de_columnas);
}

void Worker::setCalc(char *operacion){
    if (strcmp(operacion, "sum")==0){
        this->replace_flag = false;
        process(sumar);
    } else if (strcmp(operacion, "mean")==0){
        this->replace_flag = false;
        process(sumar);
    } else if (strcmp(operacion, "max")==0){
        this->replace_flag = true;
        this->max_flag = true;
        process(max);
    } else{
        this->replace_flag = true;
        this->max_flag = false;
        process(min);
    }
}

void Worker::organize(){
    bool termino=false;
    index = cola->pop(&termino);
    while (!termino){
        this->numeros = this->parser.read_index(index);
        columna = index.columna;
        setCalc(index.op);
        index = cola->pop(&termino);
    }
}

void Worker::work(){
    organize();
}

Worker::~Worker(){
}
