#include <iostream>
#include <string>
#include <vector>
#include <unordered_map>

#include"other.h"

int getting_index(std::string key, std::vector<std::string> value, std::unordered_map<std::string,std::string> matching)
{
    for(int i = 0; i < value.size(); i++)
    {
        if(value[i] == matching[key])
        {
            return(i);
        }
    }
    return(-1); // returning -1 to get rid of the warning: control may reach end of non-void function
}

int getting_index(std::string key, std::vector<std::string> value, std::string X)
{
    for(int i = 0; i < value.size(); i++)
    {
        if(value[i] == X)
        {
            return(i);
        }
    }
    return(-1); // returning -1 to get rid of the warning: control may reach end of non-void function
}

std::unordered_map<std::string,std::vector<std::string> > creating_modified_tables(std::unordered_map<std::string,std::vector<std::string> > preference_table,
std::unordered_map<std::string,std::string> matching)
{
    std::unordered_map<std::string,std::vector<std::string>> preference_table_mod;
    for(auto& p : preference_table)
    {
        std::string key{p.first};
        std::vector<std::string> value{p.second};
        int end{getting_index(key, value, matching)};
        
        std::vector<std::string> new_values;
        for(int i = 0; i < end; i++)
        {
            new_values.push_back(value[i]);
        }
        
        preference_table_mod[key] = new_values;
    }
    return(preference_table_mod);
}



