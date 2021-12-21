
# Deterministic Finite Automata (DFA) Simulator

Simulates a given DFA on a list of strings and returns whether each string is accepted or rejected by the DFA.




## Usage

You will need to create two text files -- one which specifies the configuration of the DFA and one with a list of strings to run through the DFA.

An example of the formatting of a DFA config file is as follows:

```
q0 q1 q2 q3      // list of all the states of the DFA (ordering is not important)
q0               // the starting state of the DFA
q2 q3            // a list of the final (accepting) states of the DFA
q0 a q1          // ...
q1 b q2          // a list of all transitions of the DFA in the format: start_state symbol end_state
q2 a q1          // ...
```

An example text file with a list of strings to simulate on is as follows:

```
abab
abba
0abab
abababababababab
aba
```

To run the program, compile the code with:

`gcc main.c -o program_name`

And run with:

`./program_name <dfa_config.txt> <strings_list.txt>`

