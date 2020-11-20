#ifndef ROUTER_H
#define ROUTER_H
#include <iostream>
#include <string>
#include <map>

class Router {
private: // Private variables

public: // Public varibles
    std::map<std::string, int> links; // Contains every link the node has. the string is the node it is linked to and the int represents the cost of said link
    std::map<std::string, int>::iterator links_iterator;

private: // Private methods

public: // Public methods
    Router();
    void add_link(std::string destino, int costo = -1);
    void modify_link(std::string destino, int costo);
    void delete_link(std::string destino);
    void unlink(std::string destino);
    bool is_linked(std::string destino); // checks if a specific link exists
    bool is_linked(); // checks is the node is linked at all
    void view_links(bool group); // group parameter determines whehter the router displays itself or not
};

#endif // ROUTER_H
