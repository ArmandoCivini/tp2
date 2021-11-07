#ifndef _COLAINDXSEGURA_H
#define _COLAINDXSEGURA_H

#include <queue>
#include <mutex>
#include <condition_variable>
#include <string>

//uso una clase publica aca por problemas con cppcheck
class IndexArchivo {
public:
    int comienzo;
    int cantidad_de_bytes;
    int columna;
    std::string op;
    IndexArchivo
    (int empieza, int filas_cargadas, int columnas
    , int cant_bytes, int columna, const std::string& op)
    : comienzo((empieza + filas_cargadas)*columnas*2)
    , cantidad_de_bytes(cant_bytes), columna(columna), op(op){}
    IndexArchivo
    ()
    : comienzo(0), cantidad_de_bytes(0), columna(0), op(""){}
};

class ColaIndxSegura
{
private:
    std::queue<IndexArchivo> cola;
    std::mutex m;
    std::condition_variable block_empty;
    std::condition_variable block_full;
    bool fin;
    int size;
    int threads;
    int finished_threads;
public:
    explicit ColaIndxSegura(int threads);
    void addTerminators(int cantidad);
    void push(IndexArchivo dato);
    IndexArchivo pop(bool *termino);
    void blockUntilEmtpy();
    void end();
    ~ColaIndxSegura();
};



#endif
