#ifndef _PROCESADOR_H
#define _PROCESADOR_H

#include "colaindxsegura.h"
#include "registro.h"
#include <string.h>
#include <mutex>
#include <algorithm>
#include <vector>

class Procesador
{
protected:
    int columna;
    int numero_de_columnas;
    std::vector<int>& numeros;
    Registro& registro;
    void calcular();
public:
    Procesador
    (const IndexArchivo& index, int numero_de_columnas
    , std::vector<int>& numeros, Registro& registro);
    virtual int operacion(int numero1, int numero2)=0;
    virtual void registrar(int resultado)=0;
    ~Procesador();
};

class ProcesadorSum : public Procesador
{
private:
    virtual int operacion(int numero1, int numero2) override;
    virtual void registrar(int resultado) override;  
public:
    ProcesadorSum
    (const IndexArchivo& index, std::vector<int>& numeros
    , int numero_de_columnas, Registro& registro);
    ~ProcesadorSum();
};

class ProcesadorMean : public Procesador
{
private:   
    virtual int operacion(int numero1, int numero2) override;
    virtual void registrar(int resultado) override; 
public:
    ProcesadorMean
    (const IndexArchivo& index, std::vector<int>& numeros
    , int numero_de_columnas, Registro& registro);
    ~ProcesadorMean();
};

class ProcesadorMin : public Procesador
{
private:
    virtual int operacion(int numero1, int numero2) override;
    virtual void registrar(int resultado) override;
public:
    ProcesadorMin
    (const IndexArchivo& index, std::vector<int>& numeros
    , int numero_de_columnas, Registro& registro);
    ~ProcesadorMin();
};

class ProcesadorMax : public Procesador
{
private: 
    virtual int operacion(int numero1, int numero2) override;
    virtual void registrar(int resultado) override;   
public:
    ProcesadorMax
    (const IndexArchivo& index, std::vector<int>& numeros
    , int numero_de_columnas, Registro& registro);
    ~ProcesadorMax();
};

#endif
