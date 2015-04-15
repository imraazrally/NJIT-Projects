#include <iostream>
#include <vector>
#include <sstream>
#include <cmath>
#include "DFA.h"

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
