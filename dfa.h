#ifndef _DFA_H
#define _DFA_H

#define MAX_STATES 50
#define MAX_TRANSITIONS 50

typedef struct {
    int start_state_id;
    int end_state_id;
    char symbol;
} Transition;

typedef struct {
    int id; // will be the state's index in the DFA's states array
    Transition transitions[MAX_TRANSITIONS];
    int num_transitions;
    char* state_label;
} State;

typedef struct {
    State states[MAX_STATES];
    int start_state_index;
    int accepting_states[MAX_STATES];
    int num_states;
    int num_accepting_states;
} DFA;

int dfa_process_string(DFA dfa, char* str);

#endif