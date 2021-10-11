#include "worker.h"
#include "file_parser.h"
#include "safequeuestring.h"
#include "registro.h"
#include "administrador.h"
#include <iostream>
#include <fstream>
#include <string.h>
#include <arpa/inet.h>
#include <queue>
#include <mutex>
#include <list>


int main(int argc, char *argv[]){
    std::mutex *m= new std::mutex;
    std::queue<char *> a;
    SafeQueueString q(a);
    q.setMutex(m);
    File_parser file(argv[1]);
    Administrador admin(atoi(argv[2]), atoi(argv[3]), &q, &file);
    char *linea = NULL; 
    size_t len;
    while (getline(&linea, &len, stdin) != -1){
        operar_linea(linea, admin, m, &q, atoi(argv[3]), atoi(argv[2]));
    }
    delete(m);
    free(linea);
    return 0;
}
