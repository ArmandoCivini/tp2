#include "worker.h"
#include "file_parser.h"
#include "safequeuestring.h"
#include "registro.h"
#include <iostream>
#include <fstream>
#include <string.h>
#include <arpa/inet.h>
#include <queue>
#include <mutex>
#include <list>



class Administrador
{
private:
    File_parser *parser;
    int columnas;
    int workers;
    SafeQueueString *cola;
public:
    Administrador(int columnas, int workers, SafeQueueString *colaa, File_parser *parser);
    void operar(int start, int end, int max_rows);
    ~Administrador();
};

Administrador::Administrador(int columnas, int workers, SafeQueueString *colaa, File_parser *parser){
    this->parser = parser;
    this->columnas = columnas;
    this->workers = workers;
    this->cola = colaa;
}

void Administrador::operar(int start, int end, int max_rows){
    this->parser->resetFile();
    int range = end - start;
    uint16_t bytes = max_rows*this->columnas*2;
    int filas_cargadas = 0;
    char *tirar = (char *)malloc(sizeof(char) * start * columnas *2);
    this->parser->read_n_char(tirar, start * columnas *2);
    free(tirar);
    while (filas_cargadas < range){
        if (cola->len()>=this->workers){
            //continue;
        }
        char *datos;
        if ((range-filas_cargadas)<max_rows){
            bytes = (range-filas_cargadas)*this->columnas*2;
            datos = (char *)malloc(sizeof(char)*(bytes+2));
            datos[0] = bytes >> 8;
            datos[1] = 0xFF & bytes;
            this->parser->read_n_char(&datos[2], bytes);
        } else{
            datos = (char *)malloc(sizeof(char)*(bytes+2));
            datos[0] = bytes >> 8;
            datos[1] = 0xFF & bytes;
            this->parser->read_n_char(&datos[2], bytes);
        }
        cola->push(datos);
        filas_cargadas += max_rows;
    }
    cola->addTerminators(this->workers);
}

Administrador::~Administrador()
{
}

void operar_linea
(char *linea, Administrador admin, std::mutex *m
, SafeQueueString *q, int workers, int columnas){
    Registro registro;
    registro.setMutex(m);
    char *start = strtok(linea,  " ");
    char *end = strtok(NULL,  " ");
    char *rows = strtok(NULL,  " ");
    char *columna = strtok(NULL,  " ");
    char *op = strtok(NULL,  " ");
    op[strlen(op)-1] = '\0';
    admin.operar(atoi(start), atoi(end), atoi(rows));
    Worker *trabajadores = (Worker *)malloc(sizeof(Worker)*workers);
    for (int i = 0; i < workers; i++){
        Worker trabajador(atoi(columna), columnas, q, &registro);
        trabajadores[i] = trabajador;
    }
    for (int i = 0; i < workers; i++){
        trabajadores[i].work(op);
    }
    if (strcmp(op, "mean")==0){
        registro.printDiv();
    } else{
        registro.printDato();
    }
    free(trabajadores);
    
}


int main(int argc, char *argv[]){
    std::mutex *m= new std::mutex;
    std::queue<char *> a;
    SafeQueueString q(a);
    q.setMutex(m);
    File_parser file(argv[1]);
    Administrador admin(atoi(argv[2]), atoi(argv[3]), &q, &file);
    char *linea = NULL; 
    //char *pnt_linea = linea;
    size_t len;
    while(getline(&linea, &len, stdin) != -1){
        operar_linea(linea, admin, m, &q, atoi(argv[3]), atoi(argv[2]));
    }
    
    delete(m);
    free(linea);
    return 0;
}
