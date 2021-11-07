#ifndef _LECTOR_H
#define _LECTOR_H

#include "colaindxsegura.h"
#include <iostream>
#include <fstream>
#include <string.h>
#include <arpa/inet.h>
#include <ios>
#include <vector>
#include <string>

class Lector
{
private:
    std::ifstream archivo;
public:
    explicit Lector(const std::string& in_archivo);
    std::vector<int> readIndex(IndexArchivo index);
    ~Lector();
};


#endif //_Lector_H
