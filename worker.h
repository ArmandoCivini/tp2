#ifndef _WORKER_H
#define _WORKER_H

#include "safequeuestring.h"
#include "registro.h"
#include <iostream>
#include <fstream>
#include <string.h>
#include <arpa/inet.h>
#include <mutex>

int sumar(int numero1, int numero2){
    return numero1 + numero2;
}

int min(int numero1, int numero2){
    return
    numero1 < numero2 ?
    numero1 : numero2;
}

int max(int numero1, int numero2){
    return
    numero1 > numero2 ?
    numero1 : numero2;
}

class Worker
{
private:
    std::mutex* m;
    SafeQueueString *cola;
    char *numeros;
    int columna;
    int numero_de_columnas;
    int pos_actual;
    int len_numeros;
    Registro *registro;
    bool replace_flag;
    bool max_flag;
    uint16_t siguiente_numero();
    void process(int (*calculo)(int, int));
    void organize(int (*calculo)(int, int));
    void setNumeroLen();
public:
    Worker
    (int columna, int numero_de_columnas
    , SafeQueueString *cola, Registro *reg);
    void work(char *operacion);
    void setMutex(std::mutex* m);
    ~Worker();
};

Worker::Worker
(int columna, int numero_de_columnas
, SafeQueueString *cola, Registro *reg){
    this->columna = columna;
    this->numero_de_columnas = numero_de_columnas;
    this->pos_actual = (columna* 2) + 2;
    this->cola = cola;
    this->numeros = NULL;
    this->registro = reg;
}

void Worker::setMutex(std::mutex* mu){
    this->m = mu;
}

void Worker::setNumeroLen(){
    u_int8_t primero, segundo;
    primero = this->numeros[0];
    segundo = this->numeros[1];
    uint16_t network_numero = (segundo<<8)+primero;
    this->len_numeros = (int)ntohs(network_numero);
    this->pos_actual = (this->columna * 2) + 2;
}

uint16_t Worker::siguiente_numero(){
    u_int8_t primero, segundo;
    if (this->pos_actual >= (this->len_numeros+2)){
        return -1;
    }
    primero = this->numeros[pos_actual];
    segundo = this->numeros[pos_actual+1];
    uint16_t network_numero = (segundo<<8)+primero;
    this->pos_actual += this->numero_de_columnas * 2;
    return ntohs(network_numero);
}

void Worker::process(int (*calculo)(int, int)){
    int resultado_actual = siguiente_numero();
    int valor_a_procesar;
    int iteraciones = this->len_numeros / (2 * this->numero_de_columnas);
    for (int i = 0; i < iteraciones-1; i++){
        valor_a_procesar = siguiente_numero();
        resultado_actual = calculo(resultado_actual, valor_a_procesar);
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
    this->registro->addPartes(iteraciones);
}

void Worker::organize(int (*calculo)(int, int)){
    int estado=0;
    while(estado == 0){
        free(this->numeros);
        this->numeros = cola->pop(&estado);
        if (this->numeros == NULL){
            continue;
        }
        this->setNumeroLen();
        process(calculo);
    }
}

void Worker::work(char *operacion){
    if (strcmp(operacion, "sum")==0){
        this->replace_flag = false;
        organize(sumar);
    } else if (strcmp(operacion, "mean")==0){
        this->replace_flag = false;
        organize(sumar);
    } else if (strcmp(operacion, "max")==0){
        this->replace_flag = true;
        this->max_flag = true;
        organize(max);
    } else{
        this->replace_flag = true;
        this->max_flag = false;
        organize(min);
    }
}

Worker::~Worker(){
    free(this->numeros);
}

#endif //_WORKER_H
