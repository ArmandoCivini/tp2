#ifndef _ADMINISTRADOR_H
#define _ADMINISTRADOR_H


#include "worker.h"
#include "file_parser.h"
#include "safequeuestring.h"
#include "registro.h"
#include <iostream>
#include <fstream>
#include <string.h>
#include <arpa/inet.h>
#include <queue>
#include <mutex>
#include <list>
#include <thread>
#include <vector>
#include <utility>
#include <memory>
#include <algorithm>



class Administrador
{
private:
    char *file;
    int columnas;
    int workers;
    SafeQueueString cola;
    Registro registro;
    std::vector<std::thread> hilos;
    std::vector<std::unique_ptr<Worker>> trabajadores;
public:
    Administrador
    (int columnas, int workers, char *file);
    void operar(int start, int end, int max_rows, int columna, char *op);
    void operar_linea(char *linea, int workers, int columnas);
    void end();
    ~Administrador();
};


#endif //ADMINISTRADOR_H
