#include "DFA.h"

void DFA:: init_transition(){//NOTE: Overloaded function with ZERO Parameters
// This method will dynamically create a #2D Array and set all values to -1
    transition=init_transition(Qstates.size(), SYMBOLS.size()); // --------------->Calling Function to Dynamically allocate the memory 
    for (unsigned i=0; i<Qstates.size(); i++){
        for (unsigned j=0; j<SYMBOLS.size(); j++) transition[i][j]=-1;
    } 
}

int** DFA:: init_transition(int state_cnt, int symbol_cnt){//NOTE: Overloaded function with 2 Parameters
// This function will dynamically alocate the memory based on No.Of.States and No.of.Symbols
    int ** trans_table=new int*[state_cnt];
    for (unsigned i=0; i<state_cnt; i++) trans_table[i]=new int [symbol_cnt];
    return trans_table;
}

void DFA:: init_5tuple(std::string line){
    int size=0;
    __VECSTRING init_state;
    std::string token="";
    // -----------INTITIALIZING the FIVE TUPLES of the DFA
    // 1- STORE ALL STATES in Qstates vector
    Qstates=get_items(strip_char(ret_split(line,'}',size),BRACES));
    size++;
                  
    // 2- STORE ALL symbols in SYMBOLS vector 
    SYMBOLS=get_items(strip_char(ret_split(line,'}',size),BRACES));
    init_transition(); // INITIALIZE TRANSITION TABLE
    size+=4;
    // 3- FILL TRANSITION TABLE
    tokenize_transition(ret_split(line,'}', size));
    size++;
                  
    // 4- INITIAL STATE of DFA
    init_state=get_items(ret_split(line,'{',size));
    this->init_state=int(init_state[0][1])-'0';
    
    // 5- STORE ACCEPTING STATES in Astates vector
    Astates=get_items(strip_char(ret_split(line,'}',size),BRACES));
}

void DFA::tokenize_transition(std::string line){
    // The parameter string will be in the format "(q1,a,q2),(q3,b,q1),....."
    int size=0;
    /*WHILE There are more transitions 
    1. Split String using ")" as a delim-> will return "(q1,a,q2"
    2. Strip any unnecessory brackets. --> will return "q1,a,q2"
    3. call fill_transition(string returned in STEP2);  
    */
    while(size<line.length()){
        fill_transition(strip_char(ret_split(line,')',size),BRACKET));
        size++;
    } 
}

void DFA::fill_transition(std::string token){
    /*WILL have input param in the format "q1,a,q2"
    1. Split string by delim ','
    2. append it to the vector.
    3. call fucntion insert_transition(vector)
    */
    __VECSTRING transition;
    int iter=0;
    if (token[0]==',') token[0]='{';
    transition=get_items(strip_char(token,BRACES));
    insert_transition(transition);
}

void DFA::insert_transition(__VECSTRING trans_vec){
    int tmp_from=0;
    int tmp_to=0;
    // Inserting the transition into the table
    transition[string_to_int(trans_vec[0])][get_symbol_col(trans_vec[1])]=string_to_int(trans_vec[2]);           
}

int DFA::string_to_int(std::string number){ //Converts A state str(Q123) to -> int(123)
    int to_int;
    for (unsigned i=1; i<number.length(); i++) to_int+= (int(number[i])-'0') * pow(10,number.length()-(i+1));
    return to_int;
}       

void DFA::print_transitions(){
    std::cout<<"\n\n\nTRANSITION TABLE"<<"\n____________\n";
    std::cout<<"    |";
    for (unsigned i=0; i<SYMBOLS.size();i++){
        std::cout<<" "<<SYMBOLS[i]<<"| ";
    }std::cout<<"\n";
                  
    for (unsigned i=0; i<Qstates.size();i++){
        std::cout<<" "<<Qstates[i]<<" |";
        for (unsigned j=0; j<SYMBOLS.size();j++){
            std::cout<<"q"<<transition[i][j]<<"| ";
        }
        std::cout<<"\n";
    }
    std::cout<<"____________\n\n";
}

__VECSTRING DFA::get_states(state_type type){
    __VECSTRING vec;
    switch(type){
        case ALL_STATES:
                      vec=Qstates;
                      break;
        case ACCEPT_STATES:
                      vec=Astates;
                      break;
        case ALL_SYMBOLS:
                      vec=SYMBOLS;
    }  
    return vec;
}


void DFA::print_vec(__VECSTRING vec){ 
    for (unsigned i=0; i<vec.size(); i++){
        std::cout<<vec[i]<<" ";
    }std::cout<<"\n";
}


int DFA::get_symbol_col(std::string ch){
// Given a Symbol, which index in the column does it belong to ?
    for (unsigned i=0; i<SYMBOLS.size();i++){
        if (SYMBOLS[i]==ch) return i;
    }
    std::cout<<("CHAR NOT FOUND");
    return 0;
}

int DFA::get_value(int state_in, int symbol_read){
    return transition[state_in][symbol_read];
}
             
int DFA::get_init_state(){ // Return Initial State
    return init_state;
}
             
int DFA::get_sizeof_states(__VECSTRING vec){
    return vec.size();
}
