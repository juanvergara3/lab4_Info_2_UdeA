#include "functions.h"

bool is_number(std::string s){

    for(unsigned long long k = 0; k<s.length(); k++){

        if(isdigit(s[k]) == false) return false;

    }
    return true;
}

int get_cost(bool can_be_negative){

    int cost;

    if(can_be_negative == false){
        while(true){
            std::cout<<"Ingresa el costo del enlace (0 - 100): ";
            std::cin>>cost;

            while(std::cin.fail()) { //validacion de entrada
                std::cin.clear();
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(),'\n');
                system("CLS");
                std::cout << "Opcion no valida"<<std::endl;
                std::cout<<"Ingresa el costo del enlace (0 - 100): "; std::cin>>cost;
            }


            if(cost>0 && cost <=100) break;

            else {
                system("CLS");
                std::cout<<"Costo fuera de rango"<<std::endl;
            }
        }
    }

    else{
        while(true){
            std::cout<<"Ingresa el costo del enlace (0 - 100, o -1 para desenlazar): ";
            std::cin>>cost;

            while(std::cin.fail()) { //validacion de entrada
                std::cin.clear();
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(),'\n');
                system("CLS");
                std::cout << "Opcion no valida"<<std::endl;
                std::cout<<"Ingresa el costo del enlace (0 - 100, o -1 para desenlazar): "; std::cin>>cost;
            }

            if(cost == -1) break;

            else if(cost>0 && cost <=100) break;

            else {
                system("CLS");
                std::cout<<"Costo fuera de rango"<<std::endl;
            }
        }
    }
    return cost;
}

short network_creation_menu(){

    std::string menu =
            "|  Menu de creacion de red  |\n"
            "|                           |\n"
            "| 1. Importar red           |\n"
            "| 2. Generar red            |\n"
            "| 3. Crear red manualmente  |\n"
            "| 4. Salir                  |";

    short selec;

    system("CLS");

    std::cout<<char(218);
    for(int k = 0; k<27; k++) std::cout<<char(196);
    std::cout<<char(191)<<std::endl;
    std::cout<<menu<<std::endl;
    std::cout<<char(192);
    for(int k = 0; k<27; k++) std::cout<<char(196);
    std::cout<<char(217)<<std::endl;

    std::cout<<"-> ";std::cin>>selec;

    while(std::cin.fail()) { //validacion de entrada
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(),'\n');
        system("CLS");
        std::cout<<menu<<std::endl;
        std::cout << "Opcion no valida"<<std::endl;
        std::cout<<"-> "; std::cin>>selec;
    }
    system("CLS");

    return selec;
}

short network_edit_menu()
{
    std:: string menu =
            "|     Menu de edicion de red    |\n"
            "|                               |\n"
            "| 1. Agregar router             |\n"
            "| 2. Eliminar router            |\n"
            "| 3. Visualizar router          |\n"
            "| 4. Agregar enlace             |\n"
            "| 5. Eliminar enlace            |\n"
            "| 6. Editar enlace              |\n"
            "| 7. Exportar red               |\n"
            "| 8. Ver tabla de enrutamiento  |\n"
            "| 9. Usar algoritmo de Dijkstra |\n"
            "| 10. Crear nueva red           |\n"
            "| 11. Salir                     |";

    short selec;

    std::cout<<char(218);
    for(int k = 0; k<31; k++) std::cout<<char(196);
    std::cout<<char(191)<<std::endl;
    std::cout<<menu<<std::endl;
    std::cout<<char(192);
    for(int k = 0; k<31; k++) std::cout<<char(196);
    std::cout<<char(217)<<std::endl;

    std::cout<<"-> ";std::cin>>selec;

    while(std::cin.fail()) { //validacion de entrada
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(),'\n');
        system("CLS");
        std::cout<<menu<<std::endl;
        std::cout << "Opcion no valida"<<std::endl;
        std::cout<<"-> "; std::cin>>selec;
    }
    system("CLS");

    return selec;
}
