#include "network.h"

int Network::minDistance(int *dist, bool *sptSet){
    int min = INT_MAX, min_index;

    for (int v = 0; v < number_of_routers; v++)
        if (sptSet[v] == false && dist[v] <= min && dist[v] != -1)
            min = dist[v], min_index = v;

    return min_index; 
}

void Network::printPath(int *parent, int j) {
    //if (parent[j] == - 1 || j == 0)
      if (parent[j] == - 1)
        return;

    printPath(parent, parent[j]);

    std::cout<<routers[j]<<' ';
}

void Network::printSolution(int *dist,  int *parent, int origin, int destiny){

    if(dist[destiny] < INT_MAX && dist[destiny] > 0){

        printf("Conexion\tCosto\tCamino");

        std::cout<<'\n'<<routers[origin]<<" -> "<<routers[destiny]<<"\t\t"<<dist[destiny]<<"\t"<<routers[origin]<<' ';

        printPath(parent, destiny);
    }
    else std::cout<<"No existe ningun camino entre "<<routers[origin]<<" y "<<routers[destiny]<<std::endl;
}

void Network::fill_graph(int **graph){

    std::string key1, key2;

    for(int i = 0; i < number_of_routers; i++){

        key1 = routers[i];

        for(int j = 0; j < number_of_routers; j++){

            key2 = routers[j];

            graph[i][j] = routing_table[key1].links[key2];

        }
    }
}

void Network::delete_graph(int **graph){

    for(int i = 0; i < number_of_routers; ++i) {
        delete[] graph[i];
    }
    delete[] graph;
}

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

        Router r;

        routers.insert(std::pair<int, std::string>(number_of_routers, name)); //gets added to the list of routers
        number_of_routers++;

        for(int i = 0; i<number_of_routers; i++){ //create links with all routers

            if(name == routers[i])
                r.add_link(routers[i], 0);
            else
                r.add_link(routers[i]);
        }

        routing_table.insert(std::pair<std::string, Router>(name, r)); //add new router to routing table

        for(routing_table_iterator=routing_table.begin(); routing_table_iterator != routing_table.end(); routing_table_iterator++) //adding a link with "name" to all existing routers
            routing_table_iterator->second.add_link(name);
    }
}

void Network::delete_router(std::string name){

        routing_table.erase(name); //delete router from routing table

        for(routing_table_iterator = routing_table.begin(); routing_table_iterator != routing_table.end(); routing_table_iterator++) //deleting all links with 'name' from all existing routers
            routing_table_iterator->second.delete_link(name);

        if(routing_table.size()>1){ // Creates a new "number_of_routers" that doesn't include "name"
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
}

void Network::display_router(std::string name){

    std::cout<<name<<'\t';
    routing_table[name].view_links(false);
}

void Network::display_all(){

    std::cout<<"\t";

    for(routing_table_iterator=routing_table.begin();routing_table_iterator != routing_table.end(); routing_table_iterator++)
        std::cout<<routing_table_iterator->first<<'\t';

    std::cout<<std::endl;

    for(routing_table_iterator=routing_table.begin();routing_table_iterator != routing_table.end(); routing_table_iterator++){
        std::cout<<routing_table_iterator->first<<'\t';
        routing_table_iterator->second.view_links(true);
        std::cout<<std::endl;
    }
}

void Network::display_details() {

    std::string r, temp = "| ";

    std::cout<<char(218);
    for(int k = 0; k<21; k++) std::cout<<char(196);
    std::cout<<char(191)<<std::endl;

    std::cout<<"| Detalles de la red: |"<<std::endl;
    std::cout<<"|                     |"<<std::endl;

    if(number_of_routers >= 10)
        std::cout<<"| Routers activos: "<<number_of_routers<<" |"<<std::endl;
    else
        std::cout<<"| Routers activos: "<<number_of_routers<<"  |"<<std::endl;

    std::cout<<"|                     |"<<std::endl;

    for(int k = 0; k< number_of_routers; k++){

        if(temp.length() < 20){

            temp += routers[k];
            temp += ", ";
        }

        if(temp.length() == 20){

            temp += "  |\n";
            r+=temp;
            temp.clear();
            temp = "| ";
        }
    }

    if(temp != "| "){

        temp += "\b\b";

        while(temp.length() < 24)
            temp += " ";

        temp += "  |\n";
        r += temp;
    }
    else{

        int index = r.rfind(",");
        std::string res;

        for(int k = 0; k< index; k++)
            res += r[k];
        res += "    |\n";
        r = res;
    }

    std::cout<< r ;

    std::cout<<"|                     |"<<std::endl;
    std::cout<<char(192);
    for(int k = 0; k<21; k++) std::cout<<char(196);
    std::cout<<char(217)<<std::endl;
}

void Network::dijkstra(std::string r1, std::string r2){

    int origin = this->get_router_code(r1);
    int destiny = this->get_router_code(r2);

    int** graph = new int*[number_of_routers]; //create 2d array

    for (int i = 0; i < number_of_routers; ++i)
        graph[i] = new int[number_of_routers];

    fill_graph(graph);

    int dist[number_of_routers];
    bool sptSet[number_of_routers];
    int parent[number_of_routers];

    for (int i = 0; i < number_of_routers; i++) {

        parent[origin] = -1;

        dist[i] = INT_MAX;
        sptSet[i] = false;
    }

    dist[origin] = 0;

    for (int count = 0; count < number_of_routers - 1; count++) {

        int u = minDistance(dist, sptSet);

        sptSet[u] = true;

        for (int v = 0; v < number_of_routers; v++)

            if (!sptSet[v] && graph[u][v] && dist[u] + graph[u][v] < dist[v] && graph[u][v] != -1) {

                parent[v] = u;
                dist[v] = dist[u] + graph[u][v];
            }
    }

    printSolution(dist, parent, origin, destiny);

    delete_graph(graph);
}

int Network::get_router_code(std::string router){

    for(int k = 0; k < number_of_routers; k++)
        if(routers[k] == router)
            return k;

   return -1; //this causes an exception, but main will never actually be able to reach this >:D
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

bool Network::are_linked(std::string r1, std::string r2) {

    if(routing_table[r1].is_linked(r2) && routing_table[r2].is_linked(r1)) return true;

    return false;
}

void Network::generate_network(){

    srand(time(NULL));

    short name_code, gen_routers = 2 + (rand() % (20 - 2 + 1));
    std::string name;
    int number_of_links, r1, r2, c, prev_links = 0;

    while(gen_routers > number_of_routers){ // generate random routers

        name_code = 65 + (rand() % (90 - 65 + 1));
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
                    prev_links++;

                    break;
                }
            }
        }
    }

    number_of_links = (((number_of_routers-1) * (number_of_routers))/2) - prev_links;

    if(number_of_links > 0)
        number_of_links = 1 + (rand() % (number_of_links)); //min + (rand() % static_cast<int>(max - min + 1))

    while(number_of_links > 0){ // creates a randon number of links

        r1 = rand() % (number_of_routers);
        r2 = rand() % (number_of_routers);

        if(r1 != r2){

            if(is_present(routers[r1], routers[r2]) == false){

                c = 1 + (rand() % (100));

                modify_link(routers[r1], routers[r2], c);

                number_of_links--;
            }
        }
    }
}

void Network::import_network(std::string file_name){

    std::fstream file (file_name, std:: fstream::in | std::fstream::binary); // should it be binary tho?

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
         std::cout<<"*| Red importada correctamente |*"<<std::endl;
         Sleep(1000);
     }
     else {
         std::cout<<"!! Error importando la red !!"<<std::endl;
         Sleep(1000);
     }
}

void Network::export_network(std::string file_name){

    std::fstream file (file_name, std:: fstream::out | std::fstream::binary);

     if(file.is_open()){

         std::string data;

         std::string key1, key2;
         int cost;

         for(int i = 0; i < number_of_routers; i++){

             key1 = routers[i];

             for(int j = 0; j < number_of_routers; j++){

                 key2 = routers[j];

                 cost = routing_table[key1].links[key2];

                 if(cost>0){
                     data += key1;
                     data += ' ';
                     data += key2;
                     data += ' ';
                     data += std::to_string(cost);
                     data += "\r\n";
                 }
             }
         }

         file.write(data.c_str(), data.length());

         file.close();
         std::cout<<"Red exportada correctamente"<<std::endl;
         Sleep(1000);
     }
     else {
         std::cout<<"Error exportando la red"<<std::endl;
         Sleep(1000);
     }
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

    for(int k = 0; k<temp_index; k++)
        this->delete_router(temp[k]); 
}
