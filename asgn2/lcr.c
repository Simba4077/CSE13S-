#include "cse13s_random.h"
#include "names.h"

#include <stdio.h>
#include <string.h>
typedef enum { DOT, LEFT, CENTER, RIGHT } Position;

const Position die[6] = {
    DOT,
    DOT,
    DOT,
    LEFT,
    CENTER,
    RIGHT,
};

void update_chips(int rolls, int chips[], int num_players, int current_player);
const char *to_exit(int chips[], int num_players);
int center = 0;
int main() {

    int num_players = 3;

    printf("Number of players (3 to 11)? ");

    int scanf_result = scanf("%d", &num_players);

    if (scanf_result < 1 || num_players < 3 || num_players > MAX_PLAYERS) {
        fprintf(stderr, "Invalid number of players. Using 3 instead.\n");
        num_players = 3;
    }

    int chips[num_players];

    for (int t = 0; t < num_players; t++) {
        chips[t] = 3;
    }

    unsigned seed = 4823;
    printf("Random-number seed? ");
    scanf_result = scanf("%u", &seed);

    if (scanf_result < 1 || seed < 0 || seed > 99999) {
        fprintf(stderr, "Invalid seed. Using 4823 instead.\n");
    }

    cse13s_random_seed(seed);

    int current_player = 0;

    while (
        1) { //using a for loop just to test, otherwise must use while and then code break statement

        if (chips[current_player] == 0) {
            current_player = (current_player + 1) % num_players;
            continue;
        }
        if (chips[current_player] == 1) {
            update_chips(1, chips, num_players, current_player);
            printf(
                "%s: ends her turn with %d\n", player_name[current_player], chips[current_player]);
        }

        if (chips[current_player] == 2) {
            update_chips(2, chips, num_players, current_player);
            printf(
                "%s: ends her turn with %d\n", player_name[current_player], chips[current_player]);
        }
        if (chips[current_player] >= 3) {
            update_chips(3, chips, num_players, current_player);
            printf(
                "%s: ends her turn with %d\n", player_name[current_player], chips[current_player]);
        }

        const char *winner = to_exit(chips, num_players);

        int result;

        char strg1[] = "bad";

        result = strcmp(strg1, winner);

        if (result != 0) {
            printf("%s won!\n", winner);
            break;
        }

        current_player = (current_player + 1) % num_players;

        //put something here to break out of while loop
        //for loop ends

    } //while endsprint("right to the current player before %d", chips[current_player]);
}

void update_chips(int rolls, int chips[], int num_players, int current_player) {

    for (int i = 0; i < rolls; i++) {
        //YOU NEED TO ALSO SUBTRACT FROM PLAYERS
        int roll = cse13s_random() % 6;
        Position position = die[roll];
        if (position == DOT) {
            continue;
        } //if dot ends
        if (position == CENTER) {
            center = center + 1;

            chips[current_player] = chips[current_player] - 1;

            continue;

        } //if center ends
        if (position == LEFT) {
            if (current_player == num_players - 1) {

                chips[0] = chips[0] + 1;

                chips[current_player] = chips[current_player] - 1;

                continue;

            } else {

                chips[current_player + 1] = chips[current_player + 1] + 1;

                chips[current_player] = chips[current_player] - 1;

                continue;
            }
        } //if left ends
        if (position == RIGHT) {
            if (current_player == 0) {

                chips[num_players - 1] = chips[num_players - 1] + 1;

                chips[current_player] = chips[current_player] - 1;

                continue;
            } else {

                chips[current_player - 1] = chips[current_player - 1] + 1;

                chips[current_player] = chips[current_player] - 1;

                continue;
            }
        } //if right ends
    } //for loop ends

} //function update_chips ends

const char *to_exit(int chips[], int num_players) {
    int count = 0;
    for (int t = 0; t < num_players; t++) {
        if (chips[t] > 0) {
            count++;
        }
    }
    if (count < 2) { //means end of game, only one person has chips
        for (int t = 0; t < num_players; t++) {
            if (chips[t] != 0) {
                return (player_name[t]);
            }
        }
    }
    return ("bad");
}
