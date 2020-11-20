#ifndef NETWORK_H
#define NETWORK_H
#include "router.h"
//#include "functions.h"
#include <fstream>
#include <cstdlib>
#include <time.h>
#include <windows.h>
#include <limits.h>
#include <stdio.h>

class Network {
private: // Private variables
std::map<std::string, Router> routing_table; // Contains every link. The string represents the node's name and the Router contains the links of said node
std::map<std::string, Router>::iterator routing_table_iterator;

int number_of_routers = 0;
std::map<int, std::string> routers; // Contains every node, but as an int key. It makes some tasks like dijkstra's algorithm much easier

public: // Public variables

private: // Private methods: All of these are used by dijkstra's algorithm
    int minDistance(int *dist, bool *sptSet);
    void printPath(int *parent, int j);
    void printSolution(int *dist, int *parent, int origin, int destiny);

    void fill_graph(int **graph);
    void delete_graph(int **graph);

    int get_router_code(std::string router);

public: // Public methods
    Network();

    bool is_empty();

    bool is_present(std::string r); // Checks whether a router exists or not
    bool is_present(std::string r1, std::string r2); // Checks whether a link between r1 and r2 exists or not

    void add_router(std::string name);
    void delete_router(std::string name);

    void display_router(std::string name);
    void display_all();
    void display_details();

    void dijkstra(std::string r1, std::string r2);

    void add_link(std::string r1, std::string r2, int cost);
    void delete_link(std::string r1, std::string r2);
    void modify_link(std::string r1, std::string r2, int cost);
    bool are_linked(std::string r1, std::string r2);

    void generate_network();

    void import_network(std::string file_name);
    void export_network(std::string file_name);

    void empty_network();

    void verify_integrity();
};

#endif // NETWORK_H
