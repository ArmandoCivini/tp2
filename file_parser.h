#ifndef _FILE_PARSER_H
#define _FILE_PARSER_H

#include <iostream>
#include <fstream>
#include <string.h>
#include <arpa/inet.h>
#include <ios>

class File_parser
{
private:
    std::ifstream file;
public:
    explicit File_parser(const char *file);
    void read_n_char(char *buf, int n);
    void resetFile();
    ~File_parser();
};

File_parser::File_parser(const char *in_file){
    this->file.open(in_file);
}

void File_parser::read_n_char(char *buf, int n){
    this->file.read(buf, n);
}

void File_parser::resetFile(){
    this->file.seekg(0, std::ios::beg);
    this->file.clear();
}

File_parser::~File_parser(){
    this->file.close();
}

#endif //_FILE_PARSER_H
