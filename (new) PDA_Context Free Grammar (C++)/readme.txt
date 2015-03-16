Documentation by Imraaz Rally
-----------------------------
-Documented, Designed, and Coded by Imraaz Rally 
-This Project implements a Pushdown Automata (PDA) with a Stack that recognizes the following Context-free Grammar(CFG).

S ? $T$
T ? T+T | T-T | T*T | T/T | (T) | CX
X ? XX | C | N | _ | e
C ? a | b | c | · · · | z
N ? 0 | 1 | 2 | · · · | 9

NOTE: 
     - Restrictions->The PDA, needs to be DETERMINISTIC (DFA) not an (NFA).
     - The drawing of the PDA is hosted as "PDA_drawing.pdf" under currrent working directory


---------------------TRANSITION TABLE (designed by Imraaz Rally)------------------------------------------------------------
        			 |  $   | {+,-,/,* } | {0-9} u{_} | {a-z}|   (   |  )  |  Other |   
			-------------------------------------------------------------------------
			   Q0    |1~$   | "6~~"      |"6~~"       |"6~~" | "6~~" |      |      | 
			------------------------------------------------------------------------
			   Q1    |6~~   | "6~~"      |"6~~"       |"2~~" | "1~(" |      |      | 
			-------------------------------------------------------------------------			
                           Q2    |5$~   | "3~~"      |"2~~"       |"2~~" | "6~~" |      |      | 
			-------------------------------------------------------------------------
			   Q3    |6~~   | "6~~"      |"6~~"       |"2~~" | "1~(" |      |      | 
			-------------------------------------------------------------------------
			   Q4    |5$~   | "1~~"      |"6~~"       |"6~~" | "6~~" |      |      | 
 			-------------------------------------------------------------------------
			   Q5    |6~~   | "6~~"      |"6~~"       |"6~~" | "6~~" |      |      | 
 			-------------------------------------------------------------------------
			   Q6    |6~~   | "6~~"      |"6~~"       |"6~~" | "6~~" |      |      | 
 			-------------------------------------------------------------------------
	**NOTE: Refe

--------------------Understanding the Transition Table--------------------------------------------------------------------

Suppose simple PDA, Alphabet = {$}

      	     $,'',-->$
----->(q1)------------->((Q2))

This will be intepreted as, 
		- at state(q1), if you read a '$'; then
			- pop (epsilon)
			- push($)
			- Move to State (Q2)



The transition table for this simple PDA, (according to my program), will be,

			         | '$'  | 
			-----------------
			   Q1    | 2~$  |
			-----------------

Intepretation of table:
	- At state Q1, if you read a '$' then----> value= 2~$
	- Where Value is an instruction in the form MOVE-POP-PUSH

--------------------Value Encoding of Transition Table---------------------------------------------------


Instead of having seperate column for each value to be popped, pushed, and next_state, I stored 
all of them in a single '3-char' string. Where,
	- 1st char = Next state to go to;
	- 2nd char = char to be popped()
	- 3rd char = char to be pushed()
This way, upon understanding the value encoding, the rest is simple. 

	   ****Every VALUE in the TABLE is an INSTRUCTION********
---------------------------------------------------------------------------------------------------------
	
