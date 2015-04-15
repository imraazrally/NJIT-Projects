#include <iostream>
#include <vector>
#include <sstream>
#include <cmath>

#ifndef DFA_H
#define DFA_H

typedef std::vector <std::string> __VECSTRING;
typedef enum {BRACES,BRACKET} strip_type;
typedef enum {ALL_STATES, ACCEPT_STATES, ALL_SYMBOLS} state_type;
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
             
             void init_transition();
             int** init_transition(int state_cnt, int symbol_cnt);
             void init_5tuple(std::string line);
             void tokenize_transition(std::string line);
             void fill_transition(std::string token);
             void insert_transition(__VECSTRING trans_vec);
             void print_vec(__VECSTRING vec);
             int string_to_int(std::string number);
             void print_transitions();
             __VECSTRING get_states(state_type type);           
             int get_symbol_col(std::string ch);
             int get_value(int state_in, int symbol_read);
             int get_init_state();
             int get_sizeof_states(__VECSTRING vec);
             
      private:
             std::string encoded;
             int init_state;
             int curr_state;
             __VECSTRING Qstates;
             __VECSTRING Astates;
             __VECSTRING SYMBOLS;
             
};


#endif
