#ifndef _PARSER_H
#define _PARSER_H

#include "dfa.c"

DFA read_dfa_from_file();
int get_index_of_state_label(char* label, char** state_labels);

#endif