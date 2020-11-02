#include "network.h"
#include "functions.h"
#include <limits>
#include <windows.h>

int main()
{

    //variable declaration

    Network local_network;

    // local_network.import_network("test_network.txt");
    //system("CLS");

    bool loop1 = true, gen = false;
    short selec;
    int cost, key;

    std::string menu1 =
            "1. Importar red\n"
            "2. Generar red\n"
            "3. Crear red manualmente\n"
            "4. Salir\n"

            , name1, name2,

            menu2 =
            "1. Agregar router\n"
            "2. Eliminar router\n"
            "3. Visualizar router\n"
            "4. Agregar enlace\n"
            "5. Eliminar enlace\n"
            "6. Editar enlace\n"
            "7. Exportar red\n"
            "8. Ver tabla de enrutamiento\n"
            "9. Encontrar camino mas eficiente entre 2 routers\n"
            "10. Crear nueva red\n";


    //Menu starts here

    while(loop1){

        //something that checks is the network is empty
        // and if all nodes have at least one link****************

        //make something to get out of menus

        if(gen == false){

            selec = menu_selection(menu1);

            switch (selec){
            case 1:{ //Importar red

                std::cout<<"Ingrese el nombre del archivo (incluyendo la extension) o -1 para cancelar: ";
                std::cin>>name1;

                if(name1 != "-1"){
                    system("CLS");
                    local_network.import_network(name1);
                    gen = true;
                }
                break;
            }
            case 2:{ //Generar red
                local_network.generate_network();
                gen = true;
                break;
            }
            case 3:{ //Crear red manualmente

                std::cout<<"Para crear una red debes agregar minimo 2 routers y un enlace ellos. Podras modificar la red despues de crearla"<<std::endl;

                std::cout<<"Ingresa el nombre del primer router: "<<std::endl;
                std::cin>>name1;
                local_network.add_router(name1);

                std::cout<<"Ingresa el nombre del segundo router: "<<std::endl;
                std::cin>>name2;
                local_network.add_router(name2);

                cost = get_cost(false);

                local_network.modify_link(name1, name2, cost);

                gen = true;
                break;
            }
            case 4:{ //Salir
                loop1 = false;
                break;
            }
            default:{
                std::cout<<"Opcion no valida"<<std::endl;
                break;
            }
            }
        }

        if(gen == true){ // if there's an existing network

            selec = menu_selection(menu2);

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

                local_network.delete_router(name1);

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

                local_network.display_router(name1);

                std::cout<<"Presiona ESC para volver"<<std::endl;

                while(true)
                    if (GetAsyncKeyState(VK_ESCAPE))
                        break;

                break;
            }
            case 4:{ //Agregar enlace

                while(true){
                    std::cout<<"Ingrese el router origen: ";
                    std::cin>>name1;

                    if(local_network.is_present(name1) == true) break;

                    else {
                        system("CLS");
                        std::cout<<"El router no existe"<<std::endl;
                    }
                }

                while(true){
                    std::cout<<"Ingrese el router destino: ";
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
            case 5:{ //Eliminar enlace

                while(true){
                    std::cout<<"Ingrese el router origen: ";
                    std::cin>>name1;

                    if(local_network.is_present(name1) == true) break;

                    else {
                        system("CLS");
                        std::cout<<"El router no existe"<<std::endl;
                    }
                }

                while(true){
                    std::cout<<"Ingrese el router destino: ";
                    std::cin>>name2;

                    if(local_network.is_present(name2) == true) break;

                    else {
                        system("CLS");
                        std::cout<<"El router no existe"<<std::endl;
                    }
                }

                //confirmation maybe

                local_network.delete_link(name1, name2);

                break;
            }
            case 6:{ //Editar enlace

                while(true){
                    std::cout<<"Ingrese el router origen: ";
                    std::cin>>name1;

                    if(local_network.is_present(name1) == true) break;

                    else {
                        system("CLS");
                        std::cout<<"El router no existe"<<std::endl;
                    }
                }

                while(true){
                    std::cout<<"Ingrese el router destino: ";
                    std::cin>>name2;

                    if(local_network.is_present(name2) == true) break;

                    else {
                        system("CLS");
                        std::cout<<"El router no existe"<<std::endl;
                    }
                }

                cost = get_cost(false);

                local_network.modify_link(name1, name2, cost);

                break;
            }
            case 7:{ //Exportar red       ## opcional ##

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

                break;
            }
            case 10:{ //Crear nueva red

                //ask for confirmation***

                local_network.empty_network();

                gen = false;
                break;
            }
            }
        }
    }
    return 0;
}
