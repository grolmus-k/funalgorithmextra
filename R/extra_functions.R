random_preference_tables_dataframe <- function(preference_table,seed){
  set.seed(seed)
  preference_table_random <- preference_table[,sample(1:ncol(preference_table))]
  return(preference_table_random)
}

random_preference_tables_separate <- function(keys,values,seed){
  set.seed(seed)
  random_keys <- sample(keys)
  set.seed(seed)
  random_values <- sample(values)
  return(list(keys = random_keys, values = random_values))
}

random_preference_tables_together <- function(preference_table,seed){
  set.seed(seed)
  random_preference_table <- sample(preference_table)
  return(random_preference_table)
}


stable_marriage <- function(preference_table_1, preference_table_2, seed, random=TRUE){
  if(class(preference_table_1) == 'data.frame' && 
      class(preference_table_2) == 'data.frame'){
    if(random==TRUE){
      preference_table_1 <- random_preference_tables_dataframe(preference_table_1, seed)
      preference_table_2 <- random_preference_tables_dataframe(preference_table_2, seed)
    }
    matching <- rcpp_stable_marriage_dataframe(preference_table_1, preference_table_2)
    return(matching)
  }
  else if(class(preference_table_1) == 'list' &&
          class(preference_table_2) == 'list'){
    if((length(preference_table_1) == 2 && length(preference_table_2) == 2 && 
        length(preference_table_1[[2]]) != 2 && length(preference_table_2[[2]]) != 2)){
      keys_1 <- preference_table_1[[1]]
      values_1 <- preference_table_1[[2]]
      keys_2 <- preference_table_2[[1]]
      values_2 <- preference_table_2[[2]]
      if(random==TRUE){
        keys_1 <- random_preference_tables_separate(keys_1,values_1, seed)$keys
        values_1 <- random_preference_tables_separate(keys_1,values_1, seed)$values
        keys_2 <- random_preference_tables_separate(keys_2,values_2, seed)$keys
        values_2 <- random_preference_tables_separate(keys_2,values_2, seed)$values
      }
      matching <- rcpp_stable_marriage_separate(keys_1, values_1, keys_2, values_2)
      return(matching)
      
    }
    else if (length(preference_table_1) != length(preference_table_1[[1]]) &&
             length(preference_table_2) != length(preference_table_2[[1]])){
      if(random==TRUE){
        preference_table_1 <- random_preference_tables_together(preference_table_1, seed)
        preference_table_2 <- random_preference_tables_together(preference_table_2, seed)
      }
      matching <- rcpp_stable_marriage_together(preference_table_1, preference_table_2)
      return(matching)
    }
    else if (length(preference_table_1) == length(preference_table_1[[1]]) &&
             length(preference_table_2) == length(preference_table_2[[1]])){
      if(random==TRUE){
        preference_table_1 <- random_preference_tables_together(preference_table_1, seed)
        preference_table_2 <- random_preference_tables_together(preference_table_2, seed)
      }
      matching <- rcpp_stable_marriage_dataframe(preference_table_1, preference_table_2)
      return(matching)
    }
    else{
      print("Please input the preferences tables in allowed formats.")
    }
  }
  else{
    print("Please input the preferences tables in allowed formats.")
  }

  
  
  
}


