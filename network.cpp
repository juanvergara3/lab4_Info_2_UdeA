#include "network.h"

Network::Network(){

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

void Network::remove_router(std::string name){ // probably broken ******** gotta test it

    if(routing_table.find(name) != routing_table.end()){

        routing_table.erase(name); //delete router from routing table

        for(routing_table_iterator=routing_table.begin(); routing_table_iterator != routing_table.end(); routing_table_iterator++) //delting all links with name from all existing routers
            routing_table_iterator->second.delete_link(name);

        for(int i = 0; i<number_of_routers; i++) //gets deleted from the list of routers
            if(routers[i] == name){
                routers.erase(i);
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
     }
     else std::cout<<"Error de apertura"<<std::endl;
}
