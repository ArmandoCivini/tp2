#include "colaindxsegura.h"
#include <queue>
#include <mutex>
#include <condition_variable>
#include <string>

ColaIndxSegura::ColaIndxSegura(int threads) 
: size(0), threads(threads), finished_threads(0){
    fin = false;
}

void ColaIndxSegura::push(IndexArchivo dato){
    std::lock_guard<std::mutex> lock(m);
    cola.push(dato);
    ++this->size;
    block_empty.notify_all();
}



IndexArchivo ColaIndxSegura::pop(bool *termino){
    std::unique_lock<std::mutex> lock(m);
    IndexArchivo dato;
    while (size == 0){
        ++finished_threads;
        if (finished_threads == threads){
            block_full.notify_one();
            finished_threads = 0;
        }
        if (fin){
            *termino = fin;
            return dato;
        }
        block_empty.wait(lock);
    }
    dato = cola.front();
    cola.pop();
    --this->size;
    return dato;
}

void ColaIndxSegura::blockUntilEmtpy(){
    std::unique_lock<std::mutex> lock(m);
    while (size > 0){
        block_full.wait(lock);
    }
}


void ColaIndxSegura::end(){
    std::lock_guard<std::mutex> lock(m);
    fin = true;
    block_empty.notify_all();
}


ColaIndxSegura::~ColaIndxSegura(){
}
