#include "mathlib.h"
#include "messages.h"
#include "operators.h"
#include "stack.h"

#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#define BUFFER_SIZE 1024
int breaks = 0;
int mathlib = 1;
//declare strtok_r function here
int main(int argc, char **argv) {
    int opt;
    char program[7];
    strncpy(program, argv[0], sizeof(program));
    program[sizeof(program) - 1] = '\0';

    while ((opt = getopt(argc, argv, "hm")) != -1) {
        if (opt == -1) {
            break;
        }
        if (opt == 'h') {
            printf(USAGE, program);
            breaks = 1;
            break;
        } else if (opt == 'm') {
            mathlib = 2;
        }
    }
    if (breaks == 1) {
        exit(0);
    }
    while (1) {
        fprintf(stderr, "> ");
        fflush(stderr);
        //create the buffer and read stdin into buffer
        char buffer[BUFFER_SIZE];
        fgets(buffer, BUFFER_SIZE, stdin);
        if (feof(stdin)) {
            break;
        }
        //get rid of newline at the end of the buffer
        char *newline = strchr(buffer, '\n');
        if (newline != NULL) {
            memmove(newline, newline + 1, strlen(newline));
        }

        char *saveptr;
        bool error = false;
        const char *token = strtok_r(buffer, " ", &saveptr);
        double x;

        while (token != NULL && !error) {
            if (parse_double(token, &x) == true) {
                if (stack_push(x) == false) {
                    fprintf(stderr, ERROR_NO_SPACE, x);

                    error = true;
                }
            } else if (strcmp(token, "+") == 0) {
                if (apply_binary_operator(operator_add) != true) {

                    fprintf(stderr, ERROR_BINARY_OPERATOR);
                    error = true;
                }
            }

            else if (strcmp(token, "-") == 0) {
                if (apply_binary_operator(operator_sub) != true) {
                    fprintf(stderr, ERROR_BINARY_OPERATOR);
                    error = true;
                }
            }

            else if (strcmp(token, "*") == 0) {
                if (apply_binary_operator(operator_mul) != true) {
                    fprintf(stderr, ERROR_BINARY_OPERATOR);
                    error = true;
                }
            }

            else if (strcmp(token, "/") == 0) {
                if (apply_binary_operator(operator_div) != true) {
                    fprintf(stderr, ERROR_BINARY_OPERATOR);

                    error = true;
                }
            }

            else if (strcmp(token, "%") == 0) {
                if (apply_binary_operator(fmod) != true) {
                    fprintf(stderr, ERROR_BINARY_OPERATOR);
                    error = true;
                }
            }

            else if (strcmp(token, "s") == 0 && mathlib == 1) { //must do smth with opt
                if (apply_unary_operator(Sin) != true) {
                    fprintf(stderr, ERROR_UNARY_OPERATOR);
                    error = true;
                }
            }

            else if (strcmp(token, "c") == 0 && mathlib == 1) { //must do smth with opt
                if (apply_unary_operator(Cos) != true) {
                    fprintf(stderr, ERROR_UNARY_OPERATOR);
                    error = true;
                }
            }

            else if (strcmp(token, "t") == 0 && mathlib == 1) { //must do smth with opt
                if (apply_unary_operator(Tan) != true) {
                    fprintf(stderr, ERROR_UNARY_OPERATOR);
                    error = true;
                }
            }

            else if (strcmp(token, "s") == 0 && mathlib == 2) { //must do smth with opt
                if (apply_unary_operator(sin) != true) {
                    fprintf(stderr, ERROR_UNARY_OPERATOR);
                    error = true;
                }
            }

            else if (strcmp(token, "c") == 0 && mathlib == 2) { //must do smth with opt
                if (apply_unary_operator(cos) != true) {
                    fprintf(stderr, ERROR_UNARY_OPERATOR);
                    error = true;
                }
            }

            else if (strcmp(token, "t") == 0 && mathlib == 2) { //must do smth with opt
                if (apply_unary_operator(tan) != true) {
                    fprintf(stderr, ERROR_UNARY_OPERATOR);
                    error = true;
                }
            }

            else if (strcmp(token, "r") == 0) { //must do smth with opt
                if (apply_unary_operator(Sqrt) != true) {
                    fprintf(stderr, ERROR_UNARY_OPERATOR);
                    error = true;
                }
            }

            else if (strcmp(token, "a") == 0) { //must do smth with opt
                if (apply_unary_operator(Abs) != true) {
                    fprintf(stderr, ERROR_UNARY_OPERATOR);
                    error = true;
                }
            }

            else {
                double item;
                if (stack_pop(&item)) {
                    fprintf(stderr, ERROR_BAD_CHAR, token[0]);
                    error = true;
                }
            }

            token = strtok_r(NULL, " ", &saveptr);
        }

        if (!error) {
            stack_print();
            printf("\n");
        }
        stack_clear();

        (void) argc;
        (void) argv;
    }
}
