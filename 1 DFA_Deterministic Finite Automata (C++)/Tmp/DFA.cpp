#include <iostream>
#include <vector>
#include <sstream>
#include <cmath>
typedef std::vector <std::string> __VECSTRING;
typedef enum {BRACES,BRACKET} strip_type;
typedef enum {ALL_STATES, ACCEPT_STATES, ALL_SYMBOLS} state_type;
//FUNCTION PROTOTYPES
class DFA;
int item_cnt(std::string);
__VECSTRING get_items(std::string encoding);
std::string ret_split(std::string word, char delim, int & iter_pos);
std::string strip_char(std::string encoding, strip_type ch_type);
int state_found(__VECSTRING lst, std::string state);
int Edfa(DFA & dfa);
int TEST_EDFA(std::string encoding);

class DFA{
      public:
             int ** transition; // #Dynamic 2D Array
             DFA();
             DFA(std::string encoding){ // A DFA takes in an Appropriately Encoding (Assume Encoding Correct) String.
                   encoded=encoding;
                   init_5tuple(encoding); 
             }
             
             void init_transition(){//NOTE: Overloaded function with ZERO Parameters
                   // This method will dynamically create a #2D Array and set all values to -1
                   transition=init_transition(Qstates.size(), SYMBOLS.size()); // --------------->Calling Function to Dynamically allocate the memory 
                   for (unsigned i=0; i<Qstates.size(); i++){
                       for (unsigned j=0; j<SYMBOLS.size(); j++) transition[i][j]=-1;
                   } 
             }
             
             int** init_transition(int state_cnt, int symbol_cnt){//NOTE: Overloaded function with 2 Parameters
                   // This function will dynamically alocate the memory based on No.Of.States and No.of.Symbols
                   int ** trans_table=new int*[state_cnt];
                   for (unsigned i=0; i<state_cnt; i++) trans_table[i]=new int [symbol_cnt];
                   return trans_table;
             }
             
             void init_5tuple(std::string line){
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
             
             void tokenize_transition(std::string line){
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
             
             void fill_transition(std::string token){
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
             
             void insert_transition(__VECSTRING trans_vec){
                     int tmp_from=0;
                     int tmp_to=0;
                     // Inserting the transition into the table
                     transition[string_to_int(trans_vec[0])][get_symbol_col(trans_vec[1])]=string_to_int(trans_vec[2]);           
             }
             
             int string_to_int(std::string number){ //Converts A state str(Q123) to -> int(123)
                  int to_int;
                  for (unsigned i=1; i<number.length(); i++) to_int+= (int(number[i])-'0') * pow(10,number.length()-(i+1));
                  return to_int;
             }
             
             void print_transitions(){
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
             
             __VECSTRING get_states(state_type type){
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
             
             void print_vec(__VECSTRING vec){ 
                  for (unsigned i=0; i<vec.size(); i++){
                      std::cout<<vec[i]<<" ";
                  }std::cout<<"\n";
             }
             
             int get_symbol_col(std::string ch){
                  // Given a Symbol, which index in the column does it belong to ?
                  for (unsigned i=0; i<SYMBOLS.size();i++){
                      if (SYMBOLS[i]==ch) return i;
                  }
                  std::cout<<("CHAR NOT FOUND");
                  return 0;
             }
             
             int get_value(int state_in, int symbol_read){
                   return transition[state_in][symbol_read];
             }
             int get_init_state(){ // Return Initial State
                   return init_state;
             }
             
             int get_sizeof_states(__VECSTRING vec){
                  return vec.size();
             }
             
      private:
             std::string encoded;
             int init_state;
             int curr_state;
             __VECSTRING Qstates;
             __VECSTRING Astates;
             __VECSTRING SYMBOLS;
             
};


int main(int argc, char *argv[])
{
    std::string dfa_encoding="";
    bool bye=0;
    char choice;
    
    while(bye!=1){
        std::cout<<"Do you want to TEST a DFA ? Y or y:";
        std::cin>>choice;
        if (choice=='Y' || choice == 'y'){
           std::cout<<"\n Enter Encoding :";
           dfa_encoding="";
           std::cin>>dfa_encoding;
           TEST_EDFA(dfa_encoding);
        }else{
           bye=1;
        }
    }

    system("PAUSE");
    return 0;
}

int TEST_EDFA(std::string encoding){
    DFA test_dfa(encoding);
    std::cout<<"\n\n\n---------------------------------------\n";
    std::cout<<"STRING: "<<encoding<<"\n\n";
    std::cout<<"States: ";
    test_dfa.print_vec(test_dfa.get_states(ALL_STATES));
    std::cout<<"\n";

    std::cout<<"Symbols: ";
    test_dfa.print_vec(test_dfa.get_states(ALL_SYMBOLS));
    
    test_dfa.print_transitions();
    std::cout<<"\n";
    
    std::cout<<"Starting State: q"<<test_dfa.get_init_state()<<"\n";
    
    std::cout<<"Accepting States: ";
    test_dfa.print_vec(test_dfa.get_states(ACCEPT_STATES));
    std::cout<<"\n";
    
    if(Edfa(test_dfa)){
        std::cout<<"\n\n*****STRING ACCEPTED*****\n\n";
        std::cout<<"\n---------------------------------------\n\n\n";
    }else{
        std::cout<<"\n\n*****STRING REJECTED*****\n\n";
        std::cout<<"\n---------------------------------------\n\n\n";
    }
}

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
