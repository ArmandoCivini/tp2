#include "trabajador.h"
#include "lector.h"
#include "colaindxsegura.h"
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
    std::string columnas = argv[2];
    std::string trabajadores = argv[3];
    try{
        int columnas_num = std::stoi(columnas);
        int trabajadores_num = std::stoi(trabajadores);

        Administrador admin(columnas_num, trabajadores_num, argv[1]);
        std::string linea;
        while (std::getline(std::cin, linea)){
            admin.operarLinea(linea, trabajadores_num, columnas_num);
        }
        return 0;
    } catch (std::invalid_argument const &ex) {
        std::cerr << "numero invalido" << '\n';
        return 1;
    } catch (std::out_of_range const &ex) {
        std::cerr << "numero fuera de rango" << '\n';
        return 1;
    }
}
