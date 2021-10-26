#ifndef _SAFEQUEUESTRING_H
#define _SAFEQUEUESTRING_H

#include <queue>
#include <mutex>
#include <condition_variable>

//uso una clase publica aca por problemas con cppcheck
class file_indx {
public:
    int comienzo;
    int cantidad_de_bytes;
    int columna;
    char *op;
};

class SafeQueueString
{
private:
    std::queue<file_indx> cola;
    std::mutex m;
    std::condition_variable block_empty;
    std::condition_variable block_full;
    bool fin;
    int size;
    int threads;
    int finished_threads;
public:
    explicit SafeQueueString(int threads);
    void addTerminators(int cantidad);
    void push(file_indx dato);
    file_indx pop(bool *termino);
    void blockUntilEmtpy();
    void end();
    ~SafeQueueString();
};



#endif
