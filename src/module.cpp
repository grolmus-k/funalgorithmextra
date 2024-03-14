#include "Rcpp.h"
using namespace Rcpp;

#include"fundamental_algorithm.h"
#include"other.h"

std::unordered_map<std::string,std::vector<std::string>> marshall_dataframe(const DataFrame& X)
{
    std::unordered_map<std::string,std::vector<std::string>> Y;
    std::vector<std::string> keys = X.names();

    for (int i = 0; i < keys.size();i++){
        std::vector<std::string> values = X[i];
        Y[keys[i]] = values;
    }
    return Y;
}

std::unordered_map<std::string,std::vector<std::string>> marshall_keys_values_separate(const std::list<std::vector<std::string> > X, const std::vector<std::string> key)
{
    std::unordered_map<std::string,std::vector<std::string>> Y;
    int i = 0;
    for(auto& x: X){
        Y[key[i]] = x;
        i++;

    }

    return Y;
}

std::unordered_map<std::string,std::vector<std::string>> marshall_keys_values_together(const std::list<std::vector<std::string> > X)
{
    std::unordered_map<std::string,std::vector<std::string>> Y;
    for(auto& x:X){
        std::string key = x[0];
        std::vector<std::string> values;
        for (int j=1; j < x.size();j++){
            values.push_back(x[j]);
        }
        Y[key] = values;
    }

    return Y;
}

std::unordered_map<std::string,std::string> stable_marriage_dataframe(const DataFrame& preference_table_1,const DataFrame& preference_table_2)
{
    std::unordered_map<std::string,std::vector<std::string>> preferences_1 = marshall_dataframe(preference_table_1);
    std::unordered_map<std::string,std::vector<std::string>> preferences_2 = marshall_dataframe(preference_table_2);

    std::unordered_map<std::string,std::string> matching = FUNDAMENTAL_ALGORITHM(preferences_1,preferences_2);
    return matching;

}

std::unordered_map<std::string,std::string> stable_marriage_separate(const std::vector<std::string> key_1, const std::list<std::vector<std::string> > value_1, const std::vector<std::string> key_2,
const std::list<std::vector<std::string> > value_2)
{
    std::unordered_map<std::string,std::vector<std::string>> preferences_1 = marshall_keys_values_separate(value_1,key_1);
    std::unordered_map<std::string,std::vector<std::string>> preferences_2 = marshall_keys_values_separate(value_2,key_2);

    std::unordered_map<std::string,std::string> matching = FUNDAMENTAL_ALGORITHM(preferences_1,preferences_2);
    return matching;

}

std::unordered_map<std::string,std::string> stable_marriage_together(const std::list<std::vector<std::string> > preference_table_1, const std::list<std::vector<std::string> > preference_table_2)
{
    std::unordered_map<std::string,std::vector<std::string>> preferences_1 = marshall_keys_values_together(preference_table_1);
    std::unordered_map<std::string,std::vector<std::string>> preferences_2 = marshall_keys_values_together(preference_table_2);

    std::unordered_map<std::string,std::string> matching = FUNDAMENTAL_ALGORITHM(preferences_1,preferences_2);
    return matching;

}


RCPP_MODULE(marshalling) 
{
function("rcpp_marshall_dataframe", &marshall_dataframe);
function("rcpp_marshall_keys_values_separate", &marshall_keys_values_separate);
function("rcpp_marshall_keys_values_together", & marshall_keys_values_together);
}

RCPP_MODULE(stable_marriage) 
{
function("rcpp_stable_marriage_dataframe", &stable_marriage_dataframe);
function("rcpp_stable_marriage_separate", &stable_marriage_separate);
function("rcpp_stable_marriage_together", &stable_marriage_together);
}
