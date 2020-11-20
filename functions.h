#ifndef FUNCTIONS_H
#define FUNCTIONS_H
#include <string>
#include <limits>
#include <iostream>
#include <fstream>
#include "network.h"

bool is_number(std::string s);

int get_cost(bool can_be_negative);

short network_creation_menu();

short network_edit_menu(Network& N);

bool is_file_empty(std::string file_name);

bool file_exists(std::string file_name);

void create_file(std::string file_name);

#endif // FUNCTIONS_H
