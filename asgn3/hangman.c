#include "hangman_helpers.h"

#include <stdio.h>
#include <string.h>

char phrase[257];
char eliminated[6];
char guesses[27];
int length_of = 0;
int eliminate_counter = 0;
int correct_guessed = 0;
int breaks = 1;
int main(int argc, char *argv[]) {
    //first need to prompt the user for a secret phrase
    if (argc > 1) {
        printf("");
    }
    char secret[257];
    //for (int c = 0; c < (int) strlen(argv[1]); c++) {
    //  secret[c] = argv[1][c];
    //}
    strcpy(secret, argv[1]);
    //fgets(secret, sizeof(secret), stdin);
    //secret[strcspn(secret, "\n")] = '\0';

    //now we need to check if that phrase is valid
    while (1) {

        if (is_valid_secret(secret) == true) {

            printf("%s", arts[0]); //print the gallow
            printf("\n");
            printf("    Phrase: ");

            //now let's create an array for the phrase

            int j = 0;
            for (int i = 0; i < (int) strlen(secret); i++) {
                if (secret[i] == ' ') {
                    printf(" ");
                    phrase[j++] = ' '; //add a space to the array
                } else if (secret[i] == '-') {
                    printf("-");
                    phrase[j++] = '-'; //add hyphen to the array
                } else if (secret[i] == '\'') {
                    printf("'");
                    phrase[j++] = '\''; //add apostrophe to the array
                } else { //if not the first three, then char is in a-z
                    printf("_");
                    phrase[j++] = '_';
                    length_of++; //increment a-z char counter
                }
            }
            phrase[j] = '\0';
            printf("\n");
            printf("Eliminated: \n");
            printf("\n");
            break;
        } else {

            //phrase invalid
            breaks = 0;
            break;
        }
    }
    if (breaks == 0 && (int) strlen(secret) <= 256) {
        printf("the secret phrase must contain only lowercase letters, spaces, hyphens, and "
               "apostrophes\n");
        exit(1);
    }

    if (breaks == 0 && (int) strlen(secret) > 256) {

        exit(1);
    }

    //now we need to make the eliminated array and guesses array
    //five guesses allowed + terminating char
    // twenty-six potential gueses + terminating char
    //if this equals six, the player loses
    //going to compare this with length_of to exit when player wins

    while (eliminate_counter
           < 6) { //the user can guess incorrectly five times, sixth time the loop exits
        char guess = read_letter(); //user guess is stored in variable char guess

        if (guess >= 'a' && guess <= 'z') {

            int guessIndex = -1;
            for (int num = 0; num <= (int) strlen(guesses); num++) {
                if (guesses[num] == guess) {
                    guessIndex = num;
                    break;
                }
            }

            if (guessIndex != -1) {
                continue;
            }

            guessIndex = (int) strlen(guesses); //updates the guesses array with the letter
            guesses[guessIndex] = guess;

            if (string_contains_character(secret, guess) == true) {
                //the letter is in the secret phrase

                printf("%s\n", arts[eliminate_counter]);

                for (int p = 0; p < (int) strlen(secret); p++) {

                    if (secret[p] == guess) {
                        phrase[p] = guess;
                        correct_guessed++;
                    }
                }
                printf("    Phrase: ");
                for (int ix = 0; ix < (int) strlen(secret); ++ix) {
                    printf("%c", phrase[ix]);
                }
                printf("\n");

                printf("Eliminated: ");
                for (int ax = 0; ax < (int) strlen(eliminated); ++ax) {
                    printf("%c", eliminated[ax]);
                }
                printf("\n");
                printf("\n");
            }

            if (string_contains_character(secret, guess)
                == false) { //letter is not in the secret phrase

                eliminated[eliminate_counter] = guess; //add the guess to the elimianted array
                ++eliminate_counter; //update the eliminate counter

                printf("%s\n", arts[eliminate_counter]);
                printf("    Phrase: ");
                for (int ix = 0; ix < (int) strlen(secret); ++ix) {
                    printf("%c", phrase[ix]);
                }
                printf("\n");
                sort(eliminated, (int) strlen(eliminated));
                printf("Eliminated: ");
                for (int ax = 0; ax < (int) strlen(eliminated); ++ax) {
                    printf("%c", eliminated[ax]);
                }
                printf("\n");
                printf("\n");
                continue;
            }

            //end of else statement

            if (correct_guessed == length_of) {
                printf("You win! The secret phrase was: %s\n", secret);
                break;
            }
        }

        else {
            continue;
        }
    } //end of while loop
    if (eliminate_counter == 6) {
        printf("You lose! The secret phrase was: %s\n", secret);
    }

} //end of main
