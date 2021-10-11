#ifndef _SAFEQUEUESTRING_H
#define _SAFEQUEUESTRING_H

#include <queue>
#include <mutex>

class SafeQueueString
{
private:
    std::queue<char *>& cola;
    std::mutex* m;
    int size;
    int terminators;
public:
    SafeQueueString(std::queue<char *>& q);
    void setMutex(std::mutex *mu);
    void addTerminators(int cantidad);
    void push(char *dato);
    char *pop();
    char *pop(int *termino);
    int len();
    ~SafeQueueString();
};

SafeQueueString::SafeQueueString(std::queue<char *>& q) 
: cola(q){
    this->size =  0;
    this->terminators = 0;
}

void SafeQueueString::setMutex(std::mutex *mu){
    this->m = mu;
}

void SafeQueueString::addTerminators(int cantidad){
    (*m).lock();
    this->terminators += cantidad;
    (*m).unlock();
}

void SafeQueueString::push(char *dato){
    (*m).lock();
    cola.push(dato);
    ++this->size;
    (*m).unlock();
}

char *SafeQueueString::pop(){
    (*m).lock();
    if (this->size == 0){
        return NULL;
    }    
    char *dato = cola.front();
    cola.pop();
    --this->size;
    (*m).unlock();
    return dato;
}

char *SafeQueueString::pop(int *termino){
    (*m).lock();
    if (this->size == 0){
        if (this->terminators > 0){
            *termino = 1;
            --terminators;
        }
        (*m).unlock();
        return NULL;
    }    
    char *dato = cola.front();
    cola.pop();
    --this->size;
    (*m).unlock();
    return dato;
}

int SafeQueueString::len(){
    (*m).lock();
    int cola_len = this->size;
    (*m).unlock();
    return cola_len;
}

SafeQueueString::~SafeQueueString(){
}

#endif
