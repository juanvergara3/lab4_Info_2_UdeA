#ifndef ROUTER_H
#define ROUTER_H
#include <iostream>
#include <string>
#include <map>

class Router
{
private: // Variables privadas

public: // Variables publicas
    std::map<std::string, int> links; // Contiene todos los enlaces del nodo, el string es el nodo destino y el int es le costo
    std::map<std::string, int>::iterator links_iterator;

private: // Metodos privados

public: // Metodos publicos
    Router();
    ~Router();
    void add_link(std::string destino, int costo = -1);
    void modify_link(std::string destino, int costo);
    void delete_link(std::string destino);
    void unlink(std::string destino);
    bool is_linked(std::string destino);
    bool is_linked();
    void view_links(bool group);
};

#endif // ROUTER_H
