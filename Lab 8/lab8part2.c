#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>

typedef struct node {
    int visits;
    double value;
    struct Node* parent;
    struct Node* children[676];
    int childCount;
    int priorMove;
} node;

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
        for (int i = 2; row + (i - 1) * deltaRow >= 0 && row + (i - 1) * deltaRow < n && col + (i - 1) * deltaCol >= 0 && col + (i - 1) * deltaCol < n && isSameColour == false && board[row + (i - 1) * deltaRow][col + (i - 1) * deltaCol] != 'U' && board[row + (i - 1) * deltaRow][col + (i - 1) * deltaCol] != colour; i++) {
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
        for (int i = 2; row + (i - 1) * deltaRow >= 0 && row + (i - 1) * deltaRow < n && col + (i - 1) * deltaCol >= 0 && col + (i - 1) * deltaCol < n && isSameColour == false && board[row + (i - 1) * deltaRow][col + (i - 1) * deltaCol] != 'U' && board[row + (i - 1) * deltaRow][col + (i - 1) * deltaCol] != colour; i++) {
            if (board[row + i * deltaRow][col + i * deltaCol] == colour) {
                isSameColour = true;
                for (int j = 1; j < i; ++j) {
                    scoreArray[row][col]++;
                }
            }             
        }
}

int doesBlackWin(char board[][26], int n) {
        int blackTiles = 0;
        int whiteTiles = 0;
        int blackWins;
        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < n; ++j) {
                if (board[i][j] == 'B') {
                    blackTiles++;
                } else if (board[i][j] == 'W') {
                    whiteTiles++;
                }
            }
        }
        if (blackTiles > whiteTiles) {
            blackWins = 1;
        } else if (blackTiles < whiteTiles) {
            blackWins = -1;
        } else if (blackTiles == whiteTiles) {
            blackWins = 0;
        }

        return blackWins;

}

int tilesPlaced(char board[][26], int n) {
        int tileCount = 0;
        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < n; ++j) {
                if (board[i][j] != 'U') {
                    tileCount++;
                }
            }
        }
        return tileCount;
}

