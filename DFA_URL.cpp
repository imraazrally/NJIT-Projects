// Name: Imraaz Rally
// UCID: ir29
// CS341_ Project1

#include <iostream>
#include <string>
using namespace std;

//Function Prototypes
int next_state (int current_char, int current_state);
void print_DFA(string url);
void validate(int ending_state);
//Globals
int current_state=0; // The current state of the DFA; [q0,q1,q2,q3......Q18) .I am using an INT type and ignoring the prefix 'q' 
int ending_state=0;
const int accepting_state1=9;
const int accepting_state2=13;
const int accepting_state3=16;
      
    //--------------------------TRANSITION TABLE-----------------------------------------------  
    int transition[20][27]={
/*  Two-Dimentional Array which holds the values of the (Transition Function). 
    NOTE: The values in this table (2-d array) indicate which state to go to after reading a specific character from a specific state. 
    
    Ex: suppose you are now in the start state (0) and you read in char 'a', then this table indicates you should go to State (q1). 
    If you are in State (q6) and you read a (period), it indicates to goto State(q10).
    
     a,b,c,d,e,f,g,h,i,j,k,l,m,n,o,p,q,r,s,t,u,v,w,x,y,z,(.)                          (Rows: States)
   ---------------------------------------------------------                        -----------*/
    {1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,2,1,1,1,18},                          //Q0
    {1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,10},                          //Q1
    {1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,3,1,1,1,10},                          // Q2
    {1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,4,1,1,1,10},                          //Q3
    {1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,5},                           //Q4
    {6,6,7,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,18},                          //Q5
    {6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,10},                          //Q6
    {6,6,6,6,6,6,6,6,6,6,6,6,6,6,8,6,6,6,6,6,6,6,6,6,6,6,10},                          //Q7
    {6,6,6,6,6,6,6,6,6,6,6,6,9,6,6,6,6,6,6,6,6,6,6,6,6,6,17},                          //Q8
    {6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,10},                          //Q9
    {18,18,11,18,18,18,18,18,18,18,18,18,18,18,18,18,18,18,18,18,18,18,18,18,18,18,18},//Q10
    {18,18,18,18,18,18,18,18,18,18,18,18,18,18,12,18,18,18,18,18,18,18,18,18,18,18,18},//Q11
    {18,18,18,18,18,18,18,18,18,18,18,18,13,18,18,18,18,18,18,18,18,18,18,18,18,18,14},//Q12
    {18,18,18,18,18,18,18,18,18,18,18,18,18,18,18,18,18,18,18,18,18,18,18,18,18,18,18},//Q13
    {18,18,18,18,18,18,18,18,18,15,18,18,18,18,18,18,18,18,18,18,18,18,18,18,18,18,18},//Q14
    {18,18,18,18,18,18,18,18,18,18,18,18,18,18,18,16,18,18,18,18,18,18,18,18,18,18,18},//Q15
    {18,18,18,18,18,18,18,18,18,18,18,18,18,18,18,18,18,18,18,18,18,18,18,18,18,18,18},//Q16
    {18,18,11,18,18,18,18,18,18,15,18,18,18,18,18,18,18,18,18,18,18,18,18,18,18,18,18},//Q17
    {18,18,18,18,18,18,18,18,18,18,18,18,18,18,18,18,18,18,18,18,18,18,18,18,18,18,18}//Q18
    };
    
int main(int argc, char *argv[])
{
    int i=0; 
    string url;  // Input String of Characters 
    bool bye=0;  // Break for While loop
    string choice; // Y or N
    
    while (bye!=1)
    {
          cout<<"Do you want to enter a string ? Y (yes) or N (no): ";
          cin >> choice;
               
          if (choice=="n" or choice=="N"){
                          bye=1; 
          }
          else if (choice=="y" or choice=="Y"){
               cout<<"Please enter string : ";
               cin >> url; 
               current_state=0; //resetting values
               print_DFA(url); 
          }
          else{
               cout<<"Try Again: ";
          }
    }
             
}



void print_DFA(string url)
{
    int i=0;
    int index=0; 
    char read;
    /* This function, reads the input string one char at a time. After reading a character, it call's the next state function. Which will return the next state we should go to. After printing the current state,
    the function will replace the current state with the value returned as the next state. Continues until loop is over. At the end of the loop, the value of the current_state is the end state. 
    */
    std::cout<<endl<<endl<<"(Start)----->[q0]"<<endl;
    for (i=0; i<url.length();i++){
        read=url[i];
        index=int(read); 
        /* In our two-dimentional array *****int transition[20][27]******,
        the index starts from 0, 1, 2, 3, 4,.....[columns a,b,c,d,e...z, (.)]
        
        we can easily know which column by converting the character we just read using the loop, to ASCII and substracting 97 ('a' is 97 decimal). Therefore, 97-97 will give us the Index 0
        If we read a period (46 in ASCII decimal) we convert that to 26 since that is the last element (26th) of our column.  
        */
        if (index!=46){ 
            index=index-97; // If you read in a character, substract 97 from Ascii value, to find the index it belongs to in the array.  
        }else{
            index=26;    //  If you read in a period, It's the 26th index on the array. 
        }
        current_state=next_state(index,current_state); // Calls the function that will return WHICH STATE TO GO TO NEXT. Then  current_state becomes the new state.
        std::cout<<"---"<<read<<"---->[q"<<current_state<<"]"<<endl;
    }
    ending_state=current_state; 
    validate(ending_state); // Calling validate function to see if the ending state is an accepting state
}



int next_state (int current_char, int current_state)
{     // Simply cross references the values from the Transition Table and Returns which state to go to next 
      return transition[current_state][current_char]; 
}


void validate(int ending_state)
{
     // Simply validates if the ending state is any of the accepting states.
     if (ending_state==accepting_state1 or ending_state==accepting_state2 or ending_state==accepting_state3){
                                        std::cout<<endl<<endl<<"This string will be ACCEPTED"<<endl<<endl;
     }else{
                                        std::cout<<endl<<endl<<"This string will be REJECTED"<<endl<<endl;
     }
}
