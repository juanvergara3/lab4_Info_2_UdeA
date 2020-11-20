#include "router.h"

Router::Router(){

}

void Router::add_link(std::string destino, int costo) {
    if(links.find(destino) == links.end()) // if the link doesn't exist
        links.insert(std::pair<std::string, int>(destino, costo));
    else if (links[destino] == -1)
        links[destino] = costo;
}

void Router::modify_link(std::string destino, int costo) {
    if(links.find(destino) != links.end())
        links[destino] = costo;
}

void Router::delete_link(std::string destino) {
    if(links.find(destino) != links.end())
        links.erase(destino);
}

bool Router::is_linked(std::string destino) {
    if(links[destino] != -1) return true;

    else return false;
}

bool Router::is_linked() {
        for(links_iterator = links.begin(); links_iterator != links.end(); links_iterator++)
            if(links_iterator->second != -1 && links_iterator->second != 0)
                return true;

        return false;
}

void Router::view_links(bool group) {
    if(group){
        for(links_iterator = links.begin(); links_iterator != links.end(); links_iterator++)

            if(links_iterator->second != -1)
                std::cout<<links_iterator->second<<'\t';
            else
                std::cout<<'-'<<'\t';
        std::cout<<std::endl;
    }
    else{
        for(links_iterator = links.begin(); links_iterator != links.end(); links_iterator++)

            if(links_iterator->second != 0){

                if(links_iterator->second != -1)
                    std::cout<<links_iterator->first<<": "<<links_iterator->second<<'\t';
                else
                    std::cout<<links_iterator->first<<": "<<'-'<<'\t';
            }
        std::cout<<std::endl;
    }
}
