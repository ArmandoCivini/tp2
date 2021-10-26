#ifndef _FILE_PARSER_H
#define _FILE_PARSER_H

#include "safequeuestring.h"
#include <iostream>
#include <fstream>
#include <string.h>
#include <arpa/inet.h>
#include <ios>
#include <vector>

class File_parser
{
private:
    std::ifstream file;
public:
    explicit File_parser(const char *file);
    std::vector<int> read_index(file_indx index);
    ~File_parser();
};


#endif //_FILE_PARSER_H
