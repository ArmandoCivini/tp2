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
    std::string columnas = argv[2];
    std::string workers = argv[3];
    try{
        int columnas_num = std::stoi(columnas);
        int workers_num = std::stoi(workers);

        Administrador admin(columnas_num, workers_num, argv[1]);
        std::string linea;
        while (std::getline(std::cin, linea)){
            admin.operar_linea((char *)linea.c_str(), atoi(argv[3]), atoi(argv[2]));
        }
        admin.end();
        return 0;
    } catch (std::invalid_argument const &ex) {
        std::cerr << "numero invalido" << '\n';
        return 1;
    } catch (std::out_of_range const &ex) {
        std::cerr << "numero fuera de rango" << '\n';
        return 1;
    } catch (std::bad_alloc const &ex){
        std::cerr << "falla en malloc" << '\n';
        return 1;
    }
}
