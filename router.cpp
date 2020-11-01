#include "router.h"

Router::Router(){

}

Router::~Router(){

}

void Router::add_link(std::string destino, int costo){
    if(links.find(destino) == links.end()) // si el enlace no existe
        links.insert(std::pair<std::string, int>(destino, costo));

    else std::cout<<"El enlace ya existe"<<std::endl;
}

void Router::modify_link(std::string destino, int costo){
    if(links.find(destino) != links.end())
        links[destino] = costo;

    else std::cout<<"El enlace no existe"<<std::endl;
}

void Router::delete_link(std::string destino){
    if(links.find(destino) != links.end())
        links.erase(destino);
    else std::cout<<"El enlace no existe"<<std::endl;
}

void Router::view_links(){ // should it display itself??, also it make prettier
    for(links_iterator = links.begin(); links_iterator != links.end(); links_iterator++)
        std::cout<<links_iterator->first<<": "<<links_iterator->second<<'\t';
    std::cout<<std::endl;
}
