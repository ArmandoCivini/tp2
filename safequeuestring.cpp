#include "safequeuestring.h"
#include <queue>
#include <mutex>
#include <condition_variable>

SafeQueueString::SafeQueueString(int threads) 
: size(0), threads(threads), finished_threads(0){
    fin = false;
}

void SafeQueueString::push(file_indx dato){
    std::lock_guard<std::mutex> lock(m);
    cola.push(dato);
    ++this->size;
    block_empty.notify_one();
}



file_indx SafeQueueString::pop(bool *termino){
    std::unique_lock<std::mutex> lock(m);
    file_indx dato = {};
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

void SafeQueueString::blockUntilEmtpy(){
    std::unique_lock<std::mutex> lock(m);
    while (size > 0){
        block_full.wait(lock);
    }
}


void SafeQueueString::end(){
    std::lock_guard<std::mutex> lock(m);
    fin = true;
    block_empty.notify_all();
}


SafeQueueString::~SafeQueueString(){
}
