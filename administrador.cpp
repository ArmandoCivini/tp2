#include "administrador.h"

void hilo_worker(Worker& worker){
    worker.work();
}

Administrador::Administrador
(int columnas, int workers, char *file)
: file(file), columnas(columnas), workers(workers), cola(workers){
    for (int i = 0; i < workers; i++){
        std::unique_ptr<Worker> 
        p(new Worker(columnas, &this->cola, &registro, this->file));
        trabajadores.emplace_back(std::move(p));
    }

    std::for_each
    (trabajadores.begin(), trabajadores.end(), [&](std::unique_ptr<Worker>& trabajador) {
    hilos.push_back(std::thread(hilo_worker, std::ref(*trabajador)));
});
}

void Administrador::operar(int start, int end, int max_rows, int columna, char *op){
    int range = end - start;
    int bytes = max_rows*this->columnas*2;
    int filas_cargadas = 0;

    while (filas_cargadas < range){
        file_indx index;
        index.columna = columna;
        index.op = op;
        index.comienzo = (start + filas_cargadas)*this->columnas*2;
        if ((range-filas_cargadas)<max_rows){
            index.cantidad_de_bytes = (range-filas_cargadas)*this->columnas*2;
        } else{
            index.cantidad_de_bytes = bytes;
        }
        cola.push(index);
        filas_cargadas += max_rows;
    }
}


void Administrador::operar_linea(char *linea, int workers, int columnas){
    int start = std::stoi(strtok(linea,  " "));
    int end = std::stoi(strtok(NULL,  " "));
    int rows = std::stoi(strtok(NULL,  " "));
    int columna = std::stoi(strtok(NULL,  " "));
    char *op = strtok(NULL,  " ");

    operar(start, end, rows, columna, op);
    cola.blockUntilEmtpy();
    if (strcmp(op, "mean")==0){
        registro.printDiv();
    } else{
        registro.printDato();
    }
    registro.reset();
}

void Administrador::end(){
    cola.end();
    for (std::thread & hilo : hilos){
        hilo.join();
    }
}

Administrador::~Administrador(){
}
