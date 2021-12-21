#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "parser.c"

int main(int argc, char** argv) {
    
    if (argc != 3) {
        printf("Invalid command line arguments.\n");
        printf("Usage: ./main <dfa_config_file.txt> <input_strings.txt>\n");
        exit(1);
    }

    DFA dfa;
    dfa = read_dfa_from_file(argv[1]);

    FILE* fp;
    char* line = NULL;
    size_t line_len = 0;
    ssize_t read;

    fp = fopen(argv[2], "r");
    if (fp == NULL) {
        printf("Invalid file: %s\n", argv[2]);
        exit(1);
    }

    while ((read = getline(&line, &line_len, fp)) != -1) {

        // remove newline character from end of line
        if (line[strlen(line) - 1] == '\n') line[strlen(line) - 1] = 0;

        if (dfa_process_string(dfa, line) == 0) printf("REJECTED: %s\n", line);
        else printf("ACCEPTED: %s\n", line);

    }

    return 0;

}