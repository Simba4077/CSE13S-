#include "hangman_helpers.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

bool is_lowercase_letter(char c) {
    if (c >= 'a' && c <= 'z') {
        return true;
    } else {
        return false;
    }
}

bool is_valid_secret(const char *secret) {
    int counter = 0;
    for (int letter = 0; letter < (int) strlen(secret); letter++) {
        counter++;

        //	if(strcmp(secret[letter],'') == 0){continue;}
        //	if(strcmp(secret[letter],'\'') == 0){continue;}
        //	if(strcmp(secret[letter],') == 0){continue;}

        if (secret[letter] == '-') {
            continue;
        }
        if (secret[letter] == '\'') {
            continue;
        }
        if (secret[letter] == ' ') {
            continue;
        }

        if (is_lowercase_letter(secret[letter]) == true) {
            continue;
        } else {
            printf("invalid character: '%c'\n", secret[letter]);

            return false;
        }
    }
    if (counter <= 256) {
        return true;
    } else {
        printf("the secret phrase is over 256 characters\n");
        return false;
    }
}

bool string_contains_character(const char *s, char c) {

    for (int i = 0; i < (int) strlen(s); i++) {

        if (c == s[i]) {
            return true;
        }
    }
    return false;
}

char read_letter(void) {

    char letter;
    printf("Guess a letter: ");
    char newline;

    if (fscanf(stdin, "%c", &letter) == 1) {

        fscanf(stdin, "%c", &newline);
    }

    return letter;
}

void sort(char arr[], int n) {
    for (int i = 0; i < n - 1; i++) {
        for (int j = 0; j < n - i - 1; j++) {
            if (strcmp(&arr[j], &arr[j + 1]) > 0) {
                char temp = arr[j];
                arr[j] = arr[j + 1];
                arr[j + 1] = temp;
            }
        }
    }
}
