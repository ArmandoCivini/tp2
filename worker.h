#ifndef _WORKER_H
#define _WORKER_H

#include "safequeuestring.h"
#include "registro.h"
#include "file_parser.h"
#include <iostream>
#include <fstream>
#include <string.h>
#include <arpa/inet.h>
#include <mutex>
#include <algorithm>
#include <vector>

class Worker
{
private:
    int numero_de_columnas;
    SafeQueueString *cola;
    std::vector<int> numeros;
    Registro *registro;
    int pos_actual;
    bool replace_flag;
    bool max_flag;
    File_parser parser;
    int columna;
    file_indx index;
    uint16_t siguiente_numero();
    static int sumar(int numero1, int numero2);
    static int min(int numero1, int numero2);
    static int max(int numero1, int numero2);
    void process(int (*calculo)(int, int));
    void organize();
    void setCalc(char *operacion);
    void setNumeroLen();
public:
    Worker
    (int numero_de_columnas
    , SafeQueueString *cola, Registro *reg, char *in_file);
    void work();
    ~Worker();
};


#endif //_WORKER_H
