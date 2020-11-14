#include "network.h"
#include "functions.h"
#include <limits>
#include <windows.h>

int main()
{

    //variable declaration

    Network local_network;

    bool loop = true, sub_loop, gen = false;
    short selec;
    int cost;

    std::string name1, name2, aux;

    //Menu starts here

    while(loop){

        if(gen == false){

            selec = network_creation_menu();

            switch (selec){
            case 1:{ //Importar red

                std::cout<<"Ingrese el nombre del archivo (incluyendo la extension) o -1 para cancelar: ";
                std::cin>>name1;

                if(name1 != "-1"){
                    system("CLS");
                    local_network.import_network(name1);

                    if(local_network.is_empty() == false)
                        gen = true;
                }
                break;
            }
            case 2:{ //Generar red
                local_network.generate_network();
                gen = true;
                std::cout<<"Red generada correctamente"<<std::endl;
                Sleep(1000);
                break;
            }
            case 3:{ //Crear red manualmente

                std::cout<<"Para crear una red debes agregar minimo 2 routers y un enlace ellos. Podras modificar la red despues de crearla"<<std::endl;

                std::cout<<"Ingresa el nombre del primer router: ";
                std::cin>>name1;
                local_network.add_router(name1);

                std::cout<<"Ingresa el nombre del segundo router: ";
                std::cin>>name2;
                local_network.add_router(name2);

                cost = get_cost(false);

                local_network.modify_link(name1, name2, cost);

                gen = true;
                break;
            }
            case 4:{ //Salir
                loop = false;
                break;
            }
            }
        }

        local_network.verify_integrity();               // checks the integrity of the network and each router.
        if(local_network.is_empty()) gen = false; // Removes routers that are left alone, and takes the user back to the network creation menu when the network is not valid anymore

        else if(gen == true){ // if there's an existing network

            system("CLS");

            local_network.display_details();
            selec = network_edit_menu();

            switch (selec){
            case 1:{ //Agregar router

                while(true){
                    std::cout<<"Ingrese el nombre del nuevo router: ";
                    std::cin>>name1;

                    if(local_network.is_present(name1) == false) break;

                    else {
                        system("CLS");
                        std::cout<<"El router ya existe, por favor elige un nombre distinto"<<std::endl;
                    }
                }

                local_network.add_router(name1);

                while(true){
                    std::cout<<"El router debe tener minimo un enlace. Ingrese el nombre del router con que desea enlazarlo: ";
                    std::cin>>name2;

                    if(local_network.is_present(name2) == true) break;

                    else {
                        system("CLS");
                        std::cout<<"El router no existe"<<std::endl;
                    }
                }

                cost = get_cost(false);

                local_network.add_link(name1, name2, cost);

                break;
            }
            case 2:{ //Eliminar router

                while(true){
                    std::cout<<"Ingrese el nombre del router que desea eliminar: ";
                    std::cin>>name1;

                    if(local_network.is_present(name1) == true) break;

                    else {
                        system("CLS");
                        std::cout<<"El router no existe"<<std::endl;
                    }
                }

                while(true){ //confirmation

                    std::cout<<"Esta a punto de borrar el router "<<name1<<" y todos sus enlaces (Esto puede afectar la existencia de otros routers). Desea continuar? (Y/N): "; std::cin>>name2;

                    if(name2 == "Y" || name2 == "y"){

                        local_network.delete_router(name1);

                        std::cout<<"Router borrado correctamente";
                        Sleep(1000);

                        break;
                    }
                    else if(name2 == "N" || name2 == "n") break;
                    else {
                        system("CLS");
                        std::cout<<"Opcion no valida"<<std::endl;
                    }
                }

                break;
            }
            case 3:{ //Visualizar router

                while(true){
                    std::cout<<"Ingrese el nombre del router que desea visualizar: ";
                    std::cin>>name1;

                    if(local_network.is_present(name1) == true) break;

                    else {
                        system("CLS");
                        std::cout<<"El router no existe"<<std::endl;
                    }
                }
                system("CLS");

                local_network.display_router(name1);

                std::cout<<"\nPresiona ESC para volver"<<std::endl;

                while(true)
                    if (GetAsyncKeyState(VK_ESCAPE))
                        break;

                break;
            }
            case 4:{ //Agregar enlace

                sub_loop = true;
                while(sub_loop){
                    while(sub_loop){
                        std::cout<<"Ingrese el router origen (-1 para cancelar): ";
                        std::cin>>name1;

                        if(local_network.is_present(name1) == true) break;

                        else if(name1 == "-1") sub_loop = false;

                        else {
                            system("CLS");
                            std::cout<<"El router no existe"<<std::endl;
                        }
                    }

                    while(sub_loop){
                        std::cout<<"Ingrese el router destino(-1 para cancelar): ";
                        std::cin>>name2;

                        if(local_network.is_present(name2) == true) break;

                        else if(name2 == "-1") sub_loop = false;

                        else {
                            system("CLS");
                            std::cout<<"El router no existe"<<std::endl;
                        }
                    }

                    if(name1 != name2) break;

                    else{
                        system("CLS");
                        std::cout<<"Los routers deben ser distintos"<<std::endl;
                    }
                }

                if(sub_loop == true){

                    cost = get_cost(false);

                    local_network.add_link(name1, name2, cost);
                }


                break;
            }
            case 5:{ //Eliminar enlace

                sub_loop = true;
                while(sub_loop){
                    while(sub_loop){
                        std::cout<<"Ingrese el router origen (-1 para cancelar): ";
                        std::cin>>name1;

                        if(local_network.is_present(name1) == true) break;

                        else if(name1 == "-1") sub_loop = false;

                        else {
                            system("CLS");
                            std::cout<<"El router no existe"<<std::endl;
                        }
                    }

                    while(sub_loop){
                        std::cout<<"Ingrese el router destino(-1 para cancelar): ";
                        std::cin>>name2;

                        if(local_network.is_present(name2) == true) break;

                        else if(name2 == "-1") sub_loop = false;

                        else {
                            system("CLS");
                            std::cout<<"El router no existe"<<std::endl;
                        }
                    }

                    if(name1 != name2) break;

                    else{
                        system("CLS");
                        std::cout<<"Los routers deben ser distintos"<<std::endl;
                    }
                }

                while(sub_loop){ //confirmation

                    std::cout<<"Esta a punto de desenlazar "<<name1<<" y "<<name2<<" (Esto puede afectar su existencia en la red). Desea continuar? (Y/N): "; std::cin>>aux;

                    if(aux == "Y" || aux == "y"){

                        local_network.modify_link(name1, name2, -1);

                        std::cout<<"Enlace borrado correctamente";
                        Sleep(1000);

                        break;
                    }
                    else if(aux == "N" || aux == "n") break;
                    else {
                        system("CLS");
                        std::cout<<"Opcion no valida"<<std::endl;
                    }
                }
                break;
            }
            case 6:{ //Editar enlace

                sub_loop = true;
                while(sub_loop){
                    while(sub_loop){
                        std::cout<<"Ingrese el router origen (-1 para cancelar): ";
                        std::cin>>name1;

                        if(local_network.is_present(name1) == true) break;

                        else if(name1 == "-1") sub_loop = false;

                        else {
                            system("CLS");
                            std::cout<<"El router no existe"<<std::endl;
                        }
                    }

                    while(sub_loop){
                        std::cout<<"Ingrese el router destino(-1 para cancelar): ";
                        std::cin>>name2;

                        if(local_network.is_present(name2) == true) break;

                        else if(name2 == "-1") sub_loop = false;

                        else {
                            system("CLS");
                            std::cout<<"El router no existe"<<std::endl;
                        }
                    }

                    if(name1 != name2) break;

                    else{
                        system("CLS");
                        std::cout<<"Los routers deben ser distintos"<<std::endl;
                    }
                }

                if(sub_loop) {

                    cost = get_cost(true);

                    if(cost == -1){
                        while(sub_loop){

                            std::cout<<"Esta a punto de desenlazar "<<name1<<" y "<<name2<<" (Esto puede afectar su existencia en la red). Desea continuar? (Y/N): "; std::cin>>aux;

                            if(aux == "Y" || aux == "y"){

                                local_network.modify_link(name1, name2, cost);

                                std::cout<<"Enlace modificado correctamente";
                                Sleep(1000);

                                break;
                            }
                            else if(aux == "N" || aux == "n") break;
                            else {
                                system("CLS");
                                std::cout<<"Opcion no valida"<<std::endl;
                            }
                        }
                    }
                    else{
                        local_network.modify_link(name1, name2, cost);

                        std::cout<<"Enlace modificado correctamente";
                        Sleep(1000);
                    }
                }

                break;
            }
            case 7:{ //Exportar red

                std::cout<<"Ingrese el nombre del archivo (incluyendo la extension) o -1 para cancelar: ";
                std::cin>>name1;

                if(name1 != "-1"){
                    system("CLS");

                    if(!file_exists(name1))
                        create_file(name1);

                    if(is_file_empty(name1) == true) {

                        local_network.export_network(name1);

                    }

                    else
                        while(true){

                            std::cout<<"El archivo "<<name1<<" contiene datos y estos seran sobreescritos. Desea continuar? (Y/N): "; std::cin>>name2;

                            if(name2 == "Y" || name2 == "y"){

                                local_network.export_network(name1);

                                break;
                            }
                            else if(name2 == "N" || name2 == "n") break;
                            else {
                                system("CLS");
                                std::cout<<"Opcion no valida"<<std::endl;
                            }
                        }

                }
                break;
            }
            case 8:{ //Ver tabla de enrutamiento

                local_network.display_all();

                std::cout<<"Presiona ESC para volver"<<std::endl;

                while(true)
                    if (GetAsyncKeyState(VK_ESCAPE))
                        break;

                break;
            }
            case 9:{ //Encontrar camino mas eficiente entre 2 routers

                sub_loop = true;
                while(sub_loop){
                    while(sub_loop){
                        std::cout<<"Ingrese el router origen (-1 para cancelar): ";
                        std::cin>>name1;

                        if(local_network.is_present(name1) == true) break;

                        else if(name1 == "-1") sub_loop = false;

                        else {
                            system("CLS");
                            std::cout<<"El router no existe"<<std::endl;
                        }
                    }

                    while(sub_loop){
                        std::cout<<"Ingrese el router destino(-1 para cancelar): ";
                        std::cin>>name2;

                        if(local_network.is_present(name2) == true) break;

                        else if(name2 == "-1") sub_loop = false;

                        else {
                            system("CLS");
                            std::cout<<"El router no existe"<<std::endl;
                        }
                    }

                    if(name1 != name2) break;

                    else{
                        system("CLS");
                        std::cout<<"Los routers deben ser distintos"<<std::endl;
                    }
                }

                if(sub_loop == true){

                    system("CLS");

                    local_network.dijkstra(local_network.get_router_code(name1), local_network.get_router_code(name2));

                    std::cout<<"\n\n"<<"Presiona ESC para volver"<<std::endl;

                    while(true)
                        if (GetAsyncKeyState(VK_ESCAPE))
                            break;
                }

                break;
            }
            case 10:{ //Crear nueva red
                while(true){

                    std::cout<<"Esta a punto de borrar toda la red actual. Desea continuar? (Y/N): "; std::cin>>name1;

                    if(name1 == "Y" || name1 == "y"){

                        local_network.empty_network();
                        gen = false;

                        std::cout<<"Red borrada correctamente";
                        Sleep(1000);

                        break;
                    }
                    else if(name1 == "N" || name1 == "n") break;
                    else {
                        system("CLS");
                        std::cout<<"Opcion no valida"<<std::endl;
                    }
                }
                break;
            }
            case 11:{ //Salir
                loop = false;
                break;
            }
            }
        }
    }
    return 0;
}
