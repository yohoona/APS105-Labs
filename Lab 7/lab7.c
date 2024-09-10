#include <stdio.h>
#include <stdbool.h>

void printBoard(char board[][26], int n) {
    printf("  ");
    for (int i = 0; i < n; ++i) {
        printf("%c", (char)(i + 97));
    }
    printf("\n");
    for (int row = 0; row < n; ++row) {
        printf("%c ", (char)(row + 97));
        for (int col = 0; col < n; ++col) {
            if ((row == n / 2 - 1 && col == n / 2 - 1) || (row == n / 2 && col == n / 2)) {
                board[row][col] = 'W';
            } else if ((row == n / 2 - 1 && col == n / 2) || (row == n / 2 && col == n / 2 - 1)) {
                board[row][col] = 'B';
            } else {
                board[row][col] = 'U';
            }
            
            printf("%c", board[row][col]);
        }
            printf("\n");
    }
}

/*bool inBounds(int n, int row, int col) {
    bool inside;
    if (row <= n && col <= n && row > 0 && col > 0) {
        inside = true;
    } else {
        inside = false;
    }
    return inside;
}*/

bool checkLegal(char board[][26], int n, int row, int col, char colour, int deltaRow, int deltaCol) {
    bool legal;
    if (deltaRow == 0 && deltaCol == 0) {
        legal = false;
    } else {
        for (int i = 2; row + i * deltaRow < n && row + i * deltaRow >= 0 && col + i * deltaCol < n && col + i * deltaCol >= 0 && legal == false; ++i) {
            if (colour == 'W' && board[row][col] == 'U') {
                if (board[row + deltaRow][col + deltaCol] == 'B' && board[row + i * deltaRow][col + i * deltaCol] == 'W' && board[row + (i - 1) * deltaRow][col + (i - 1) * deltaCol] != 'U') {
                    legal = true;
                } else {
                    legal = false;
                }
            } else if (colour == 'B' && board[row][col] == 'U') {
                if (board[row + deltaRow][col + deltaCol] == 'W' && board[row + i * deltaRow][col + i * deltaCol] == 'B' && board[row + (i - 1) * deltaRow][col + (i - 1) * deltaCol] != 'U') {
                    legal = true;
                } else {
                    legal = false;
                }
            } else {
                legal = false;
            }
        }
    }
    return legal;
}

void swap(char board[][26], int n, int row, int col, char colour, int deltaRow, int deltaCol) {
    bool isSameColour = false;
    for (int i = 2; row + (i - 1) * deltaRow >= 0 && row + (i - 1) * deltaRow < n && col + (i - 1) * deltaCol >= 0 && col + (i - 1) * deltaCol < n && isSameColour == false && board[row + (i - 1) * deltaRow][col + (i - 1) * deltaCol] != 'U'; i++) {
        if (board[row + i * deltaRow][col + i * deltaCol] == colour) {
            isSameColour = true;
            for (int j = 0; j < i; ++j) {
                board[row + j * deltaRow][col + j * deltaCol] = colour;
            }
        }             
    }
}


void updateBoard(char board[][26], int n) {
     printf("  ");
    for (int i = 0; i < n; ++i) {
        printf("%c", (char)(i + 97));
    }
    printf("\n");
    for (int row = 0; row < n; ++row) {
        printf("%c ", (char)(row + 97));
        for (int col = 0; col < n; ++col) {         
            printf("%c", board[row][col]);
        }
        printf("\n");
    }
}

int main() {
    int n;
    char board[26][26];
    printf("Enter the board dimension: ");
    scanf("%d", &n);

    
    printBoard(board, n);

    char colour, row, col;
    printf("Enter board configuration:\n");

    do {
        scanf(" %c%c%c", &colour, &row, &col);

        board[row - 97][col - 97] = colour;
    } while (colour != '!' && row != '!' && col != '!');

    updateBoard(board, n);

    bool allowed;

    printf("Available moves for W: ");
    for (row = 0; row < n; ++row) {
        for (col = 0; col < n; ++col) {
            allowed = false;
            for (int i = -1; i < 2 && allowed == false; ++i) {
                for (int j = -1; j < 2 && allowed == false; ++j) { 
                    allowed = checkLegal(board, n, row, col, 'W', i, j);              
                    if (allowed == true) {
                            printf("\n%c%c", (char)(row + 97), (char)(col + 97));
                    }
                }
            }
        }
    }

    printf("\nAvailable moves for B: ");
    for (row = 0; row < n; ++row) {
        for (col = 0; col < n; ++col) {
            allowed = false;
            for (int i = -1; i < 2 && allowed == false; ++i) {
                for (int j = -1; j < 2 && allowed == false; ++j) {
                    allowed = checkLegal(board, n, row, col, 'B', i, j);                
                    if (allowed == true) {
                        printf("\n%c%c", (char)(row + 97), (char)(col + 97));
                    }
                }
            }
        }
    }


    printf("\nEnter a move:\n");
    scanf(" %c%c%c", &colour, &row, &col);
    allowed = false;
    for (int i = -1; i < 2 && allowed == false; ++i) {
        for (int j = -1; j < 2 && allowed == false; ++j) {
            allowed = checkLegal(board, n, row - 97, col - 97, colour, i, j);
        }
    }

    if (allowed == true) {
        printf("Valid move.\n");
        for (int i = -1; i < 2; ++i) {
            for (int j = -1; j < 2; ++j) {
                swap(board, n, row - 97, col - 97, colour, i, j);
            }
        }
        updateBoard(board, n);
    } else {
        printf("Invalid move.\n");
        updateBoard(board, n);
    }

    return 0;
}