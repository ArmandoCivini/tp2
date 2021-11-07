#include "lector.h"
#include <iostream>
#include <fstream>
#include <string.h>
#include <arpa/inet.h>
#include <ios>
#include <vector>
#include <string>

Lector::Lector(const std::string& in_archivo): archivo(in_archivo){
}

std::vector<int> Lector::readIndex(IndexArchivo index){
    this->archivo.seekg(index.comienzo);
    std::vector<char> buf(index.cantidad_de_bytes);
    
    this->archivo.read(buf.data(), index.cantidad_de_bytes);
    std::vector<int> numeros;
    for (int i = 0; i < index.cantidad_de_bytes; i+=2){
        numeros.push_back((int)ntohs(*(uint16_t *)&buf[i]));
    }
    return numeros;
}


Lector::~Lector(){
    this->archivo.close();
}
