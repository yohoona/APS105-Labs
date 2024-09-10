    #include "lab8part1.h"
    #include <stdio.h>

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

    bool positionInBounds(int n, int row, int col) {
        bool inside;
        if (row <= n && col <= n && row > 0 && col > 0) {
            inside = true;
        } else {
            inside = false;
        }
        return inside;
    }

    bool checkLegalInDirection(char board[][26], int n, int row, int col, char colour, int deltaRow, int deltaCol) {
        bool legal = false;
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

    void moveScore(char board[][26], int scoreArray[][26], int n, int row, int col, char colour, int deltaRow, int deltaCol) {
        bool isSameColour = false;
        for (int i = 2; row + (i - 1) * deltaRow >= 0 && row + (i - 1) * deltaRow < n && col + (i - 1) * deltaCol >= 0 && col + (i - 1) * deltaCol < n && isSameColour == false && board[row + (i - 1) * deltaRow][col + (i - 1) * deltaCol] != 'U'; i++) {
            if (board[row + i * deltaRow][col + i * deltaCol] == colour) {
                isSameColour = true;
                for (int j = 1; j < i; ++j) {
                    scoreArray[row][col]++;
                }
            }             
        }
    }



    int main() {
        int n;
        char board[26][26];
        printf("Enter the board dimension: ");
        scanf("%d", &n);

        /*char compColour;
        printf("Computer plays (B/W): ");
        scanf(" %c", &compColour);*/

        printBoard(board, n);

        char colour, row, col;
        printf("Enter board configuration:\n");

        do {
            scanf(" %c%c%c", &colour, &row, &col);

            board[row - 97][col - 97] = colour;
        } while (colour != '!' && row != '!' && col != '!');

        updateBoard(board, n);

        int scoreArray[26][26] = {0};

        char validMoves[676][3];
        bool allowed;
        int numValidMoves = 0;
        for (row = 0; row < n; ++row) {
            for (col = 0; col < n; ++col) {
                allowed = false;
                for (int i = -1; i < 2 && allowed == false; ++i) {
                    for (int j = -1; j < 2 && allowed == false; ++j) { 
                        allowed = checkLegalInDirection(board, n, row, col, 'W', i, j);              
                        if (allowed == true) {
                            validMoves[numValidMoves][0] = (char)(row + 97);
                            validMoves[numValidMoves][1] = (char)(col + 97);
                            numValidMoves++;

                            moveScore(board, scoreArray, n, row, col, 'W', i, j);

                        }
                    }
                }
            }
        }


        printf("Here are all valid moves for player W: \n");
        for (int i = 0; i < numValidMoves; ++i) {
            for (int j = 0; j < 2; ++j) {
                printf("%c", validMoves[i][j]);
            }
            printf("\n");
        }

        printf("Here is how many opponent tiles each move would flip: \n");
        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < n; ++j) {
                printf("%d ", scoreArray[i][j]);
            }
            printf("\n");
        }

        int bestMove = 0;
        int bestMoveRow;
        int bestMoveCol;
        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < n; ++j) {
                if (scoreArray[i][j] > bestMove) {
                    bestMove = scoreArray[i][j];
                    bestMoveRow = i;
                    bestMoveCol = j;
                }
            }
        }

        printf("This is what happens after making the first best move: \n");
        for (int i = -1; i < 2; ++i) {
            for (int j = -1; j < 2; ++j) {
                swap(board, n, bestMoveRow, bestMoveCol, 'B', i, j);
            }
        }
        updateBoard(board, n);



    return 0;

}