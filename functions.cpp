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

short menu_selection(std::string menu){

    short selec;

    system("CLS");
    std::cout<<menu<<std::endl;
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
