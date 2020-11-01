#ifndef NETWORK_H
#define NETWORK_H
#include "router.h"
#include "functions.h"
#include <fstream>
#include <cstdlib>

class Network
{
private: // Variables privadas
std::map<std::string, Router> routing_table; //contiene todos los nodos, el string es el nombre del nodo, y el Router contiene los enlaces de dicho nodo
std::map<std::string, Router>::iterator routing_table_iterator;

int number_of_routers  = 0;
std::map<int, std::string> routers;

public: // Variables publicas

private: // Metodos privados

public: // Metodos publicos
    Network();
    void add_router(std::string name);
    void remove_router(std::string name);
    void display_router(std::string name);
    void display_all();
    void generate_network();
    void import_network(std::string file_name);
    void export_network(std::string file_name); // opcional. revisar si el archivo contiene cosas antes de escribir
};

#endif // NETWORK_H
