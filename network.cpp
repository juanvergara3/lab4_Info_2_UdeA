#include "network.h"

Network::Network(){

}

bool Network::is_empty(){

    if(routing_table.empty()) return true;
    else return false;
}

bool Network::is_present(std::string r){
    if(routing_table.find(r) != routing_table.end()) return true;
    else return false;
}

bool Network::is_present(std::string r1, std::string r2){

    if(routing_table.find(r1) != routing_table.end()){

        if(routing_table.find(r2) != routing_table.end()){

            if(routing_table[r1].is_linked(r2) && routing_table[r2].is_linked(r1)) return true;

        }
        else return false;
    }
    else return false;
}

void Network::add_router(std::string name){

    if(routing_table.find(name) == routing_table.end()){

        /*Router r; //doesn't take itself in account

        for(int i = 0; i<number_of_routers; i++) //create links with all routers
            r.add_link(routers[i]);

        routers.insert(std::pair<int, std::string>(number_of_routers, name)); //gets added to the list of routers
        number_of_routers++;

        for(routing_table_iterator=routing_table.begin(); routing_table_iterator != routing_table.end(); routing_table_iterator++) //adding a link with name to all existing routers
            routing_table_iterator->second.add_link(name);

        routing_table.insert(std::pair<std::string, Router>(name, r)); //add new router to routing table*/

        Router r; //takes itself in account

        routers.insert(std::pair<int, std::string>(number_of_routers, name)); //gets added to the list of routers
        number_of_routers++;

        for(int i = 0; i<number_of_routers; i++){ //create links with all routers

            if(name == routers[i])
                r.add_link(routers[i], 0);
            else
                r.add_link(routers[i]);
        }

        routing_table.insert(std::pair<std::string, Router>(name, r)); //add new router to routing table

        for(routing_table_iterator=routing_table.begin(); routing_table_iterator != routing_table.end(); routing_table_iterator++) //adding a link with name to all existing routers
            routing_table_iterator->second.add_link(name);

    }
    else std::cout<<"El router "<<name<<" ya existe"<<std::endl;
}

void Network::delete_router(std::string name){ // probably broken ******** gotta test it

    if(routing_table.find(name) != routing_table.end()){

        routing_table.erase(name); //delete router from routing table

        for(routing_table_iterator=routing_table.begin(); routing_table_iterator != routing_table.end(); routing_table_iterator++) //delting all links with name from all existing routers
            routing_table_iterator->second.delete_link(name);

        for(int i = 0; i<number_of_routers; i++) //gets deleted from the list of routers
            if(routers[i] == name){
                routers.erase(i);
                number_of_routers--; //what if it gets removed from the middle???? **********
                break;
            }
    }
    else std::cout<<"El router no existe"<<std::endl;
}

void Network::display_router(std::string name){ // ****** make prettier

    if(routing_table.find(name) != routing_table.end()){
        std::cout<<name<<'\t';
        routing_table[name].view_links();
    }

    else std::cout<<"El router no existe"<<std::endl;
}

void Network::display_all(){ // ****** make prettier

    for(routing_table_iterator=routing_table.begin();routing_table_iterator != routing_table.end(); routing_table_iterator++){

        std::cout<<routing_table_iterator->first<<'\t';
        routing_table_iterator->second.view_links();
        std::cout<<std::endl;
    }
}

void Network::add_link(std::string r1, std::string r2, int cost){ //this might or might not work ******

    routing_table[r1].add_link(r2, cost);
    routing_table[r2].add_link(r1, cost);
}

void Network::delete_link(std::string r1, std::string r2){ //this might or might not work ******

    routing_table[r1].delete_link(r2);
    routing_table[r2].delete_link(r1);
}

void Network::modify_link(std::string r1, std::string r2, int cost){ //this might or might not work ******

    routing_table[r1].modify_link(r2, cost);
    routing_table[r2].modify_link(r1, cost);
}

void Network::generate_network(){ //empty ******

}

void Network::import_network(std::string file_name){ // seems to be working just fine ******* gotta test it further

    std::fstream file (file_name, std:: fstream::in | std::fstream::binary); // should it be binary tho ?

     if(file.is_open()){

         std::string temp, r1, r2;
         int cost;
         short counter = 1;

         while (file >> temp){

             if(counter == 1){ //router 1
                 r1 = temp;
                 add_router(r1);
             }
             else if (counter == 2){ //router 2
                 r2 = temp;
                 add_router(r2);
             }
             else if (counter == 3){ //cost
                 cost = stoi(temp);

                 routing_table[r1].modify_link(r2, cost);
                 routing_table[r2].modify_link(r1, cost);

                 counter = 0;
             }

             counter++;
         }
         file.close();
         std::cout<<"Red importada correctamente"<<std::endl;
     }
     else std::cout<<"Error importando la red"<<std::endl;
}

void Network::empty_network()
{

}
