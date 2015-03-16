#include <cstdlib>
#include <iostream>

using namespace std;
// ------------Function Prototypes---------------------------------------------- 
void DFA_push(char); // Calls ^ Push() after performing certain validations 
void DFA_pop(char); // Calls pop() after performing certain validations.  
void process_string(string); 
string transition(int, char); // return a value from the PDA Table
int return_col(char); //will return which column in the PDA table to go to.
void status(); // Prints whether string is, Accepted or Rejected or Crashed
void push(char); // Pushes a CHAR into the stack
char pop(); // Simply pops the top most CHAR and returns the value
void print_stack(); 
void print(int, char, char, char); 
//------------------------------------------------------------------------------
struct stack{
       char ch;
       struct stack * top;       
}; 
struct stack * head=NULL;

//Subsets of the Alphabet
char E_op[4]={'+','-','/','*'}; 
char E_ch[26]={'a','b','c','d','e','f','g','h','i','j','k','l','m','n','o','p','q','r','s','t','u','v','w','x','y','z'}; //a-z
char E_n[11]={'0','1','2','3','4','5','6','7','8','9','_'}; //0-9
const int accept_state=5;
int current_state=0;
bool state_crash=0;
/*---------------------TRANSITION TABLE-----------------------------------------
This is the TRANSITION Function of the Push-Down-Automota(PDA)
-NOTE: The symbol '~' means Epsilon
       -Rows are [States], Columns are subset of [symbols]
    
-A value in the table is an Instruction in the form [Move][Pop][Push]
-ex, Suppose you are in state q0 and read symbol '$', 
     the instruction returned will be "1~$".     
-That instruction means, Goto State(1), Pop(~Epsilon), Push($) 
*/
string PDA[7][7]={
//(Column)  $    E_op   E_n    E_ch     (       )   NOT(E)
//                                                         (ROW)
         {"1~$", "6~~","6~~", "6~~", "6~~", "6~~", "6~~"}, //q0     
         {"6~~", "6~~","6~~", "2~~", "1~(", "6~~", "6~~"}, //q1 
         {"5$~", "3~~","2~~", "2~~", "6~~", "4(~", "6~~"}, //q2
         {"6~~", "6~~","6~~", "2~~", "1~(", "6~~", "6~~"}, //q3
         {"5$~", "1~~","6~~", "6~~", "6~~", "4(~", "6~~"}, //q4
         {"6~~", "6~~","6~~", "6~~", "6~~", "6~~", "6~~"}, //q5
         {"6~~", "6~~","6~~", "6~~", "6~~", "6~~", "6~~"}  //q6                 
                           
};
//---------------------------------------Main()---------------------------------

int main(int argc, char *argv[])
{
    string word;
    string choice;
    bool bye=0;
    
    while(bye!=1){
        cout<<"Do you want to enter a string ? Y (yes) or N (no): ";
        cin >> choice;
        if (choice=="n" or choice=="N"){
            bye=1; 
        } else if (choice=="y" or choice=="Y"){
            cout<<"Please enter string : "; cin >> word; cout<<endl<<endl;
            current_state=0;
            state_crash=0; //resetting values
            process_string(word); // Process the String that was entered.
            status();
            cout<<endl<<endl;
        }else{
            cout<<"Incorrect Input-Try Again: ";
        }              
    }  
}

//----------------------------------End of Main()-------------------------------

void process_string(string word){
    /* This function will read the input string CHAR by CHAR, 
            - for each character, 
              - refer to the PDA and retrieve the instruction 
              - Process the instruction (MOVE-POP-PUSH)
              - Print each transition
    */
    int i=0;
    string instruction; //MOVE-POP-PUSH
    cout<<"Start State: q0"<<endl;
    for (i=0; i<word.length(); i++){
        if (state_crash==1){
            break;
        }
        instruction=transition(current_state, word[i]);
        current_state=atoi(&instruction[0]);
        DFA_pop(instruction[1]);
        DFA_push(instruction[2]);
        print(current_state,word[i],instruction[1],instruction[2]);
    }

}



string transition(int current_state, char c){
/*
Based on the [current_state] and the [Symbol Read], What to do next ?
Returns an instruction (move-pop-push) fetched from the PDA Table.
*/
    return  PDA[current_state][return_col(c)];  
    // Looks up PDA Table based on [current_state][Column the char belongs to]
}

int return_col(char c){
/*
NOTE: 
The Columns in PDA Table are not symbols, they are [Subset of symbols] 
So, before we lookup the table, we need to know which subset the CHAR belongs to
This function will return the INDEX of the column a Symbol(Char) belongs to.
Ex: '$' belongs to index 0, '5' belongs to index 2...etc 
*/
       int i=0;
             
       if (c=='(' ) return 4; 
       if (c==')' ) return 5;
       if (c=='$' ) return 0;
       
       for (i=0; i<4; i++){
           if (c==E_op[i]) return 1;
       }
       
       for (i=0; i<26; i++){
           if (c==E_ch[i]) return 3;
       }
       
       for (i=0; i<11; i++){
           if (c==E_n[i])return 2;
       } 
       
       return 6;
}

void DFA_pop(char c){
     /* NOTE-> -A PDA can pop an Epsilon.---> DO nothing
               -A PDA pop must check if the popped symbol matches  
     */
     char ch;
     if (c=='~') return; // If (Episilon), do nothing
     ch=pop();
     if (ch!=c)  state_crash=1;//If the popped symbol doesn't match, PDA Crashes
}

void DFA_push(char c){
     // Push a symbol only if symbol is not (Epsilon).
     if (c != '~') push(c); 
}

//----------------------(Generic Stack functions)-------------------------------

void push(char c){     
     struct stack * node;
     struct stack * current=head;
     node=new struct stack;
     node->ch=c;
     node->top=NULL;
     
     if (head==NULL){
         head=node;
     }else{
         while(current->top){
         current=current->top;
         }
         current->top=node;
     }
           
}

char pop(){
     struct stack * current=head;
     struct stack * current_prev=head;
     char ch;
     
     if (head==NULL){
         state_crash=1;
         return '%';
     }else if (head->top==NULL){
         ch=head->ch;
         head=NULL;
         return ch;
     }else{
         while(current->top){
             current=current->top;
             if (current->top){
                 current_prev=current_prev->top;
             }
         }
         ch=current->ch;
         current_prev->top=NULL;
         return ch;
     }
}

//--------------------------(PRINT Functions)-----------------------------------
void status(){
     if (state_crash==1){
         cout<<"CRASHED"<<endl;
     }else if (current_state==accept_state){
         cout<<"ACCEPTED"<<endl;
     }else{
         cout<<"REJECTED"<<endl;
     }
}


void print_stack(){
     struct stack * current=head;
     if (head==NULL){
         cout<<"No items in stack"<<endl;
     }else{
         while(current){
             cout<<current->ch;
             current=current->top;
         }
     }
}

void print(int current_state, char read, char popped, char pushed){
     //Symbol Read: Symbol Popped: Symbol Pushed: Current State:
     cout<<"Read  : "<<read;
     if (popped=='~'){ 
         cout<<"  Popped:(epsilon)";
     }else{
         cout<<"  Popped:        "<<popped;
     }
     
     if (pushed=='~'){
         cout<<"  Pushed:(epsilon)";
     }else{
         cout<<"  Pushed:        "<<pushed;
     }
     cout<<"  Current State:q"<<current_state<<endl;
}
