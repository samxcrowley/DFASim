#include "dfa.h"

int dfa_process_string(DFA dfa, char* input_str) {

    size_t input_str_len = strlen(input_str);

    int current_state_index = dfa.start_state_index;

    for (int i = 0; i < input_str_len; i++) {
        
        char symbol = input_str[i];
        State current_state = dfa.states[current_state_index];

        int found_trans = 0;

        for (int j = 0; j < current_state.num_transitions; j++) {
            
            Transition trans = current_state.transitions[j];

            if (trans.symbol == symbol) {
                current_state_index = trans.end_state_id;
                found_trans = 1;
                break;
            }

        }

        if (found_trans == 0) {
            return 0;
        }

        if (i == input_str_len - 1) {

            int accepted = 0;
            
            for (int j = 0; j < dfa.num_accepting_states; j++) {
                if (dfa.accepting_states[j] == current_state_index) {
                    accepted = 1;
                }
            }

            return accepted;

        }

    }

    return 0;

}