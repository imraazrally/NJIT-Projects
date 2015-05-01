int Edfa(DFA & dfa){
    std::stringstream out;
    std::string in_state;
    __VECSTRING open_lst;
    out<<dfa.get_init_state(); // INT to STR
    
    open_lst.push_back("q"+out.str()); // Initiall, the open_lst contains only the initial state. (which can be reaches from itself)
    std::cout<<"S= "; dfa.print_vec(open_lst);
    
    for (unsigned i=0; i<open_lst.size(); i++){
        for (unsigned j=0; j<dfa.get_sizeof_states(dfa.get_states(ALL_SYMBOLS)); j++){
            out.str("");
            out<<dfa.transition[dfa.string_to_int(open_lst[i])][j];
            in_state="q"+out.str();
            if (!state_found(open_lst,in_state)) open_lst.push_back(in_state);
        }
        std::cout<<"S= "; dfa.print_vec(open_lst); 
    }
    // Iterate through [S] which is Open_lst and check to see if you have any elements in Accepting States
    for (unsigned i=0; i<open_lst.size(); i++){
        if(state_found(dfa.get_states(ACCEPT_STATES),open_lst[i]))
            return 0;
    }
    return 1;
}

int state_found(__VECSTRING lst, std::string state){
    for (unsigned i=0; i<lst.size(); i++){
        if (lst[i]==state) return 1;
    }
    return 0;
}


std::string strip_char(std::string encoding, strip_type ch_type){
    //Function to strip a string out of either [Braces] or [Brackets]
    std::string line="";
    char ch_left, ch_right;
    
    switch(ch_type){
                 case BRACES:
                       ch_left='{';
                       ch_right='}';
                       break;
                       
                 case BRACKET:
                       ch_left='(';
                       ch_right=')';
                       break;
    }
    
    for (unsigned i=0; i<encoding.length(); i++){
          if (encoding[i]!=ch_left && encoding[i]!=ch_right) line+=encoding[i];
    }
    return line;
}


__VECSTRING get_items(std::string encoding){
    //TAKES IN A COMMA SEPERATED STRING 
    // RETURNS A VECTOR OF STRINGS (SPLIT by delim ',')
    std::string token;
    __VECSTRING items;
    for (int i=0; i<encoding.length();i++){
          token=ret_split(encoding,',',i);
          if (token.length()>0){
              items.push_back(token);
          } 
    }
    return items;
}

std::string ret_split(std::string word, char delim, int & iter_pos){
    // WORKS LIKE strtok(). WILL RETURN A STRING
    std::string ret_string="";
    unsigned iter=iter_pos;
    while(word[iter]!=delim && iter<word.length()) ret_string+=word[iter++];    
    iter_pos+=ret_string.length();        
    return ret_string;
}

