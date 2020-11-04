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

            if(routing_table[r1].is_linked(r2) && routing_table[r2].is_linked(r1))
                return true;

            else return false;
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
    //else std::cout<<"El router "<<name<<" ya existe"<<std::endl;
}

void Network::delete_router(std::string name){

   // if(routing_table.find(name) != routing_table.end()){ //these if statements are likely useless

        routing_table.erase(name); //delete router from routing table

        for(routing_table_iterator = routing_table.begin(); routing_table_iterator != routing_table.end(); routing_table_iterator++) //deleting all links with 'name' from all existing routers
            routing_table_iterator->second.delete_link(name);

        if(routing_table.size()>1){
            std::map<int, std::string>temp;
            int temp_index = 0;

            for(int i = 0; i<number_of_routers; i++)
                if(routers[i] != name){
                    temp.insert(std::pair<int, std::string>(temp_index, routers[i]));
                    temp_index++;
                }
            routers = temp;
            number_of_routers = temp_index;
        }

        else this->empty_network();
    //}
    //else std::cout<<"El router no existe"<<std::endl;
}

void Network::display_router(std::string name){

    if(routing_table.find(name) != routing_table.end()){
        std::cout<<name<<'\t';
        routing_table[name].view_links(false);
    }

    else std::cout<<"El router no existe"<<std::endl;
}

void Network::display_all(){

    std::cout<<"\t";

    for(routing_table_iterator=routing_table.begin();routing_table_iterator != routing_table.end(); routing_table_iterator++){

        std::cout<<routing_table_iterator->first<<'\t';

    }
    std::cout<<std::endl;

    for(routing_table_iterator=routing_table.begin();routing_table_iterator != routing_table.end(); routing_table_iterator++){

        std::cout<<routing_table_iterator->first<<'\t';
        routing_table_iterator->second.view_links(true);
        std::cout<<std::endl;
    }
}

void Network::add_link(std::string r1, std::string r2, int cost){

    routing_table[r1].add_link(r2, cost);
    routing_table[r2].add_link(r1, cost);
}

void Network::delete_link(std::string r1, std::string r2){

    routing_table[r1].delete_link(r2);
    routing_table[r2].delete_link(r1);
}

void Network::modify_link(std::string r1, std::string r2, int cost){

    routing_table[r1].modify_link(r2, cost);
    routing_table[r2].modify_link(r1, cost);
}

void Network::generate_network(){ //i swear to god if this keeps failing smh

    srand(time(NULL));

    short name_code, gen_routers = 2 + (rand() % (20 - 2 + 1));
    std::string name;
    int number_of_links, r1, r2, c;

    while(gen_routers > number_of_routers){ // generate random routers

        name_code = rand() %26 + 65;
        name = char(name_code);

        if(is_present(name) == false)
            add_router(name);
    }

    for(int i = 0; i < number_of_routers; i++){ // makes sure each router has at least 1 link

        if(routing_table[routers[i]].is_linked() == false){

            while(true){

                name_code = rand() % number_of_routers;

                if(name_code != i){

                    c = 1 + (rand() % (100));

                    add_link(routers[i], routers[name_code], c);

                    break;
                }
            }
        }
    }

    number_of_links = (number_of_routers)*(number_of_routers - 2);
    number_of_links = rand() % (number_of_links + 1);

    while(number_of_links >= 0){ // creates a randon number of links

        r1 = rand() % (number_of_routers + 1); //min + (rand() % static_cast<int>(max - min + 1))
        r2 = rand() % (number_of_routers + 1);

        if(r1 != r2){

            if(is_present(routers[r1], routers[r2]) == false){

                c = 1 + (rand() %(100));

                modify_link(routers[r1], routers[r2], c);

                number_of_links--;
            }
        }
    }
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
         Sleep(1000);
     }
     else {
         std::cout<<"Error importando la red"<<std::endl;
         Sleep(1000);
     }
}

void Network::export_network(std::string file_name){

}

void Network::empty_network(){
    routers.clear();
    routing_table.clear();
    number_of_routers = 0;
}

void Network::verify_integrity(){

    std::map<int, std::string> temp;
    int temp_index = 0;

    for(routing_table_iterator = routing_table.begin(); routing_table_iterator != routing_table.end(); routing_table_iterator++){

        if(routing_table_iterator->second.is_linked() == false){

            temp[temp_index] = routing_table_iterator->first;
            temp_index++;
        }
    }

    for(int k = 0; k<temp_index; k++){

        this->delete_router(temp[k]);

    }
}
