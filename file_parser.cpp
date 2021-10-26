#include "file_parser.h"
#include <iostream>
#include <fstream>
#include <string.h>
#include <arpa/inet.h>
#include <ios>
#include <vector>

File_parser::File_parser(const char *in_file){
    this->file.open(in_file);
}

std::vector<int> File_parser::read_index(file_indx index){
    this->file.seekg(index.comienzo);
    char *buf = (char *)malloc(index.cantidad_de_bytes*sizeof(char));
    if (buf == NULL) throw std::bad_alloc();
    
    this->file.read(buf, index.cantidad_de_bytes);
    std::vector<int> numeros;
    u_int8_t primero, segundo;
    for (int i = 0; i < index.cantidad_de_bytes; i+=2){
        primero = buf[i];
        segundo = buf[i+1];
        uint16_t network_numero = (segundo<<8)+primero;
        numeros.push_back((int)ntohs(network_numero));
    }
    free(buf);
    return numeros;
}


File_parser::~File_parser(){
    this->file.close();
}
