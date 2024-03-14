#include <iostream>
#include <string>
#include <vector>
#include <unordered_map>

#include"fundamental_algorithm.h"
#include"other.h"

std::unordered_map<std::string,std::string> FUNDAMENTAL_ALGORITHM(std::unordered_map<std::string,std::vector<std::string>> preference_table_1,
std::unordered_map<std::string,std::vector<std::string>> preference_table_2)
{
    std::vector<std::string> keys_1;
    std::vector<std::string> keys_2;
    std::unordered_map<std::string,std::string> matching;
    
    for(auto& p1 : preference_table_1)
    {
        // Creating a vector of keys
        keys_1.push_back(p1.first);
    }
    
    for(auto& p2 : preference_table_2)
    {
        // Creating a vector of keys
        keys_2.push_back(p2.first);
        // Adding the 'very undesirable men' to the women's preference table
        p2.second.push_back("Omega");
    }

    // Creating a matching with all the mean and women and women's preference is set to the 'very undesirable men'
    for (auto& m : keys_1)
    {
        matching[m] = {};
    }
    
    for (auto& f : keys_2)
    {
        matching[f] = "Omega";
    }
    
    int n;
    n = keys_1.size();

    for(int k = 0; k < n; k++)
    {
        std::string X;
        X = keys_1[k];
        while(X != "Omega")
        {
            std::string x;
            x = preference_table_1[X][0];
            int index_1;
            index_1 = getting_index(x, preference_table_2[x], matching);
            int index_2;
            index_2 = getting_index(x, preference_table_2[x], X);
    
            if (index_1 > index_2)
            {
                std::string previous_matching;
                previous_matching = matching[x];
                matching[X] = x;
                matching[x] = X;
                X = previous_matching;
            }
            if (X != "Omega")
            {
                preference_table_1[X].erase(preference_table_1[X].begin());
                matching[X] = {};
            }
        }
    }
    return(matching);
}
