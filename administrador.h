#ifndef _ADMINISTRADOR_H
#define _ADMINISTRADOR_H


#include "trabajador.h"
#include "lector.h"
#include "colaindxsegura.h"
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
#include <string>


class Administrador
{
private:
    std::string file;
    int columnas;
    int trabajadores_num;
    ColaIndxSegura cola;
    Registro registro;
    std::vector<std::thread> hilos;
    std::vector<Trabajador> trabajadores;
    void operar(int start, int end, int max_rows, int columna, const std::string& op);
public:
    Administrador
    (int columnas, int Trabajadors, char *file);
    void operarLinea(const std::string& linea, int Trabajadors, int columnas);
    ~Administrador();
};


#endif //ADMINISTRADOR_H
