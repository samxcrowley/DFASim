#include <stdlib.h>
#include <string.h>
#include "parser.h"

DFA read_dfa_from_file(const char* file_name) {

    DFA dfa;
    dfa.num_states = 0;
    dfa.num_accepting_states = 0;
    for (int i = 0; i < MAX_STATES; i++) {
        dfa.accepting_states[i] = -1;
    }
    
    FILE* fp;
    char* line = NULL;
    size_t line_len = 0;
    ssize_t read;

    fp = fopen(file_name, "r");
    if (fp == NULL) {
        printf("Invalid file: %s\n", file_name);
        exit(1);
    }

    int line_num = 0;

    char* state_labels[MAX_STATES];

    while ((read = getline(&line, &line_len, fp)) != -1) {

        // remove newline character from end of line
        if (line[strlen(line) - 1] == '\n') line[strlen(line) - 1] = 0;

        char* token;
        token = strtok(line, " ");

        if (line_num == 0) {            // line containing list of states

            int index = 0;

            while (token != NULL) {

                // copy token into a new string as its value will be overwritten
                // in subsequent lines
                char* copy_token = malloc((strlen(token) + 1) * sizeof(char));
                strcpy(copy_token, token);

                // TODO: check for repeated listing of state (e.g. "q2 q0 q2")

                state_labels[index++] = copy_token;
                dfa.num_states++;
                
                token = strtok(NULL, " ");

            }

            // convert list of state labels to State objects in DFA
            for (int i = 0; i < dfa.num_states; i++) {

                dfa.states[i].state_label = state_labels[i];
                dfa.states[i].id = get_index_of_state_label(state_labels[i], state_labels);

            }

        } else if (line_num == 1) {     // line containing start state

            int start_index = get_index_of_state_label(token, state_labels);

            if (start_index == -1) {
                printf("Invalid start state in DFA config.\n");
                exit(0);
            }

            dfa.start_state_index = start_index;

        } else if (line_num == 2) {     // line containing list of accepting states

            int index = 0;

            while (token != NULL) {

                int state_index = get_index_of_state_label(token, state_labels);

                // TODO: check for repeated listing of state (e.g. "q2 q0 q2")

                dfa.accepting_states[dfa.num_accepting_states] = state_index;
                dfa.num_accepting_states++;

                token = strtok(NULL, " ");

            }

        } else { // lines containing list of transitions

            int trans_start_state = get_index_of_state_label(token, state_labels);
            token = strtok(NULL, " ");
            char trans_symbol = token[0];
            token = strtok(NULL, " ");
            int trans_end_state = get_index_of_state_label(token, state_labels);

            State* start = &dfa.states[trans_start_state];
            Transition* start_next_trans = &start->transitions[start->num_transitions];
            
            start_next_trans->start_state_id = trans_start_state;
            start_next_trans->symbol = trans_symbol;
            start_next_trans->end_state_id = trans_end_state;

            start->num_transitions++;

        }

        line_num++;

    }

    fclose(fp);
    if (line) free(line);

    return dfa;

}

// given an array of state labels, return which index a label has in that array
int get_index_of_state_label(char* label, char** state_labels) {

    for (int i = 0; i < MAX_STATES; i++) {

        if (state_labels[i] == NULL) return -1;
        
        if (strcmp(label, state_labels[i]) == 0) {
            return i;
        }

    }

    return -1;

}