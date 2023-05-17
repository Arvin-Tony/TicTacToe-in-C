#include <stdio.h>
#include <stdbool.h>
#include <assert.h>

// Input-Output based Tic-Tac-Toe Game. Instructions print when run.
// If providing an input file to the program, 

// check_arr(arr, x_or_o) checkis if the array is filled with
//   the same character
// Time: O(n)
bool check_arr(char arr[], char x_or_o) {
    assert(arr);
    
    const int arr_len = 3;
    bool in_row = true;
    
    for (int i = 0; i < arr_len; ++i) {
        if (arr[i] != x_or_o) {
            in_row = false;
            return in_row;
        }
    }
    
    return in_row;
}

// check_win(x_or_o, arr_all_horiz, arr_all_vert, arr_diag_1, arr_diag_2) 
//   takes in the the arrays representing the board and checks if 
//   a player has won
// Time: O(n)
bool check_win(char x_or_o, char* arr_all_horiz[], char* arr_all_vert[], 
                                        char arr_diag_1[], char arr_diag_2[]) {
    assert(arr_all_horiz);
    assert(arr_all_vert);
    assert(arr_diag_1);
    assert(arr_diag_2);
    
    const int arr_len = 3;
    const int arr_count = 3;
    bool win = false;
    
    for (int i = 0; i < 3; ++i) {
        if (check_arr(arr_all_horiz[i], x_or_o)) {
            win = true;
            return win;
        }
        if (check_arr(arr_all_vert[i], x_or_o)) {
            win = true;
            return win;
        }
    }
    if (check_arr(arr_diag_1, x_or_o) || check_arr(arr_diag_2, x_or_o)) {
        win = true;
        return win;
    }
    
    return win;
}

// update_diag(arr_diag_1, arr_diag_2, row, col, x_or_o) updates the 
//   respective diagonal arrays to reflect the recent play
// effects: may modify arr_diag_1 and/or arr_diag_2
void update_diag(char arr_diag_1[], char arr_diag_2[], 
                            int row, int col, char x_or_o) {
    assert(arr_diag_1);
    assert(arr_diag_2);
    assert(1 <= row && row <= 3);
    assert(1 <= col && col <= 3);
    
    if (row == col) {
        if (row == 2) arr_diag_2[1] = x_or_o;
        arr_diag_1[row - 1] = x_or_o;
    } else if (row - 2 == col) {
        arr_diag_2[0] = x_or_o;
    } else if (row + 2 == col) {
        arr_diag_2[2] = x_or_o;
    } else {
        return;
    }
    
}

// update_ver(arr_vert, row, x_or_o) updates the correct vertical array  
//  (the column) as necessary based on the recent play
// effects: modifies arr_vert
void update_vert(char arr_vert[], int row, char x_or_o) {
    assert(arr_vert);
    assert(1 <= row && row <=3);
    
    row -= 1;
    arr_vert[row] = x_or_o;

}

// update_horiz(arr_horiz, col, x_or_o) updates the correct horiztonal array
//   (the row) as necessary based on the recent play. It returns true if said
//   play was valid (ie, doesn't overlapp another non-empty space), 
//   false otherwise.
// Effects: may modifiy arr_horiz
bool update_horiz(char arr_horiz[], int col, char x_or_o) {
    assert(arr_horiz);
    assert(1 <= col && col <=3);
    col -= 1;

    if (arr_horiz[col] == '_') {
        arr_horiz[col] = x_or_o;
        return true;
    } else {
        return false;
    }
    
}

// print_board(arr_horiz_1, arr_horiz_2, arr_horiz_3) prints out the 
//   Tic-Tac-Toe board to output, with proper styling
// Effects: produces output
// Time: O(n)
void print_board(char arr_horiz_1[], char arr_horiz_2[], char arr_horiz_3[]) {
    assert(arr_horiz_1);
    assert(arr_horiz_2);
    assert(arr_horiz_3);
    const int arr_len = 3;
    
    printf("|");
    for (int i = 0; i < arr_len; ++i) {
        printf(" %c", arr_horiz_1[i]);
        printf(" |");
    }
    printf("\n");

    printf("|");
    for (int i = 0; i < arr_len; ++i) {
        printf(" %c", arr_horiz_2[i]);
        printf(" |");
    }
    printf("\n");

    printf("|");
    for (int i = 0; i < arr_len; ++i) {
        printf(" %c", arr_horiz_3[i]);
        printf(" |");
    }
    printf("\n");

}


int main() {
    
    bool player1 = true;
    
    char arr_horiz_1[3] = {'_', '_', '_'};
    char arr_horiz_2[3] = {'_', '_', '_'};
    char arr_horiz_3[3] = {'_', '_', '_'};
    
    char* arr_all_horiz[3] = {arr_horiz_1, arr_horiz_2, arr_horiz_3};
    
    char arr_vert_1[3] = {'_', '_', '_'};
    char arr_vert_2[3] = {'_', '_', '_'};
    char arr_vert_3[3] = {'_', '_', '_'};
    
    char* arr_all_vert[3] = {arr_vert_1, arr_vert_2, arr_vert_3};
    
    char arr_diag_1[3] = {'_', '_', '_'};
    char arr_diag_2[3] = {'_', '_', '_'};
    
    int turns = 0;
    
    bool table_full = false;
    bool one_win = false;
    bool two_win = false;
    
    printf("Welcome to Tic Tac Toe!\n"); 
    printf("To play the game, please enter the position you want to enter\n");
    printf("your character in as two integers: row number, column number\n");
    printf("For example, when prompted, you enter: (1, 1)\n");
    printf("Your character will print at the top left corner of the board.\n");
    printf("Note that commas and characters not neccessary, and\n");
    printf("you can separate the two numbers by anything.\n");
    printf("For example, when prompted, you enter: 1 3\n");
    printf("Your character will print at the top right corner of the board.\n");
    printf("Player 1 is 'X' and Player 2 is 'O'.\n");
    printf("If you try to place your character where a character already");
    printf("exists\nyou will be prompted to enter another point with ");
    printf("no demerit.\nAfter each turn, the current board will print.\n");
    printf("Here's the board right now:\n");
    print_board(arr_horiz_1, arr_horiz_2, arr_horiz_3);
    printf("Best of luck!\n");
    
    char x_or_o = 'X';
    
    bool first = true;
    
    char garbage = 'c';
    
    bool eof = false;
    
    while (true) {
        int row = 0;
        int col = 0;
        
        if (first) {
            first = false;
        } else {
           print_board(arr_horiz_1, arr_horiz_2, arr_horiz_3); 
        }
        
        if (player1) {
            printf("Player 1 (X), enter coordinates:\n");
        } else {
            printf("Player 2 (O), enter coordinates:\n");
        }

        // getting two valid numbers at a time, and ensuring input exists
        bool first_in = false;
        bool second_in = false;
        
        while (eof == false) {
            if (first_in == false) {
                int retval_1 = scanf("%d", &row);
                if (retval_1 == 1) {
                    first_in = true;
                } else if (retval_1 == 0) {
                    int retval_2 = scanf(" %c", &garbage);
                    if (retval_2 != 1) eof = true;
                } else {
                    eof = true;
                }
            } else if (second_in == false) {
                int retval_1 = scanf("%d", &col);
                if (retval_1 == 1) {
                    second_in = true;
                } else if (retval_1 == 0) {
                    int retval_2 = scanf(" %c", &garbage);
                    if (retval_2 != 1) eof = true;
                } else {
                    eof = true;
                }
            } else {
                break;
            }
        } 
        
        if (row == 0 || col == 0) {
            break;
        }
        
        if (row < 1 || row > 3) {
            printf("Invalid input. Please make sure your row is between 1 and 3\n");
            continue;
        }
        
        if (col < 1 || col > 3) {
            printf("Invalid input. Please make sure your column is between 1 and 3.\n");
            continue;
        }
        
        if (player1) {
            x_or_o = 'X';
        } else {
            x_or_o = 'O';
        }
        
        // update rows, columns, and diagonals
        if (!update_horiz(arr_all_horiz[row - 1], col, x_or_o)) {
            printf("Letter placed at position already, try again:\n");
            continue;
        }
        update_vert(arr_all_vert[col - 1], row, x_or_o);
        update_diag(arr_diag_1, arr_diag_2, row, col, x_or_o);
        
        // check if player has won or not
        if (check_win(x_or_o, arr_all_horiz, arr_all_vert, arr_diag_1, arr_diag_2)) {
            if (player1) {
                one_win = true;
                break;
            } else {
                two_win = true;
                break;
            }
        }
        
        ++turns;
        
        if (turns == 9) {
            table_full = true;
            break;
        }
        
        player1 = !player1;
        
        if (eof) {
            break;
        }
    }
    
    print_board(arr_horiz_1, arr_horiz_2, arr_horiz_3);
    
    if (one_win) {
        printf("Congratulations Player 1 (X)! You win!");
    } else if (two_win) {
        printf("Congratulations Player 2 (O)! You win!");
    } else if (table_full) {
        printf("Well played to both players. It's a tie!");
    }
    
    if (eof) {
        printf("You don't have enough input! Above is your final board.");
    }
    
    return 0;
}
