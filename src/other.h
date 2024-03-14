#include <iostream>
#include <string>
#include <vector>
#include <unordered_map>

#ifndef MY_PROJECT_HEADER_OTHER
#define MY_PROJECT_HEADER_OTHER

int getting_index(std::string key, std::vector<std::string> value, std::unordered_map<std::string,std::string> matching);

int getting_index(std::string key, std::vector<std::string> value, std::string X);

std::unordered_map<std::string,std::vector<std::string> > creating_modified_tables(std::unordered_map<std::string,std::vector<std::string> >, std::unordered_map<std::string,std::string>);

#endif
