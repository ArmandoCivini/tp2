#include "administrador.h"
#include <iostream>
#include <sstream>
#include <string>

Administrador::Administrador
(int columnas, int trabajadores_num, char *file)
: file(file), columnas(columnas), trabajadores_num(trabajadores_num), cola(trabajadores_num){
    for (int i = 0; i < trabajadores_num; i++){
        trabajadores.emplace_back(columnas, this->cola, registro, this->file);
    }

    std::for_each(trabajadores.begin(), trabajadores.end(), [&](Trabajador& trabajador) {
            hilos.push_back(std::thread(&Trabajador::trabajar, std::ref(trabajador)));
        });
}

void Administrador::operar(int start, int end, int max_rows, int columna, const std::string& op){
    int range = end - start;
    int bytes = max_rows*this->columnas*2;
    int filas_cargadas = 0;

    while (filas_cargadas < range){
        int cantidad_de_bytes;
        if ((range-filas_cargadas)<max_rows){
            cantidad_de_bytes = (range-filas_cargadas)*this->columnas*2;
        } else{
            cantidad_de_bytes = bytes;
        }
        IndexArchivo index(start, filas_cargadas, columnas, cantidad_de_bytes, columna, op);
        cola.push(index);
        filas_cargadas += max_rows;
    }
}


void Administrador::operarLinea(const std::string& linea, int workers, int columnas){
    std::istringstream stream(linea);
    int start, end, rows, columna;
	std::string op;
    stream  >> start >> end >> rows >> columna >> op;
    operar(start, end, rows, columna, op);
    cola.blockUntilEmtpy();
    if (op == "mean"){
        registro.printDiv();
    } else{
        registro.printDato();
    }
    registro.reset();
}

Administrador::~Administrador(){
    cola.end();
    for (std::thread & hilo : hilos){
        hilo.join();
    }
}
