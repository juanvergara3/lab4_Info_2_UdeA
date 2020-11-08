#ifndef NETWORK_H
#define NETWORK_H
#include "router.h"
#include "functions.h"
#include <fstream>
#include <cstdlib>
#include <time.h>
#include <windows.h>
#include <limits.h>
#include <stdio.h>

class Network
{
private: // Variables privadas
std::map<std::string, Router> routing_table; //contiene todos los nodos, el string es el nombre del nodo, y el Router contiene los enlaces de dicho nodo
std::map<std::string, Router>::iterator routing_table_iterator;

int number_of_routers  = 0;
std::map<int, std::string> routers;

public: // Variables publicas

private: // Metodos privados
    int minDistance(int *dist, bool *sptSet);
    void printPath(int *parent, int j);
    void printSolution(int *dist, int *parent, int origin, int destiny);

    void fill_graph(int **graph);
    void delete_graph(int **graph);

public: // Metodos publicos
    Network();

    bool is_empty();

    bool is_present(std::string r);
    bool is_present(std::string r1, std::string r2);

    void add_router(std::string name);
    void delete_router(std::string name);

    void display_router(std::string name);
    void display_all();
    void display_details();

    void dijkstra(int origin, int destiny);
    int get_router_code(std::string router);

    void add_link(std::string r1, std::string r2, int cost);
    void delete_link(std::string r1, std::string r2);
    void modify_link(std::string r1, std::string r2, int cost);

    void generate_network();

    void import_network(std::string file_name);
    void export_network(std::string file_name); // opcional. revisar si el archivo contiene cosas antes de escribir

    void empty_network();

    void verify_integrity();
};

#endif // NETWORK_H
