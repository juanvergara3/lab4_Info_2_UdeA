#include "functions.h"

bool is_number(std::string s){

    for(unsigned long long k = 0; k<s.length(); k++){

        if(isdigit(s[k]) == false) return false;

    }
    return true;
}
