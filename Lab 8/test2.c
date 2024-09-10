#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>

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

int main() {
    int n;
    char board[26][26];
    int scoreArray[26][26] = {0};
    char validMoves[676][3];

    printf("Enter the board dimension: ");
    scanf(" %d", &n);

    char compColour;
    printf("Computer plays (B/W): ");
    scanf(" %c", &compColour);
    
    printBoard(board, n);

    char row, col;
    bool allowed;
    bool valid;
    int numValidMovesB, numValidMovesW;
    int bestMove;
    int bestMoveRow;
    int bestMoveCol;
    bool gameOver = false;

    if (compColour == 'W') {
        for (int moveNumber = 0; gameOver == false; ++moveNumber) {           
            if (moveNumber % 2 == 0) {
                numValidMovesB = 0;                
                for (row = 0; row < n; ++row) {
                    for (col = 0; col < n; ++col) {
                        allowed = false;
                        for (int i = -1; i < 2 && allowed == false; ++i) {
                            for (int j = -1; j < 2 && allowed == false; ++j) { 
                                allowed = checkLegalInDirection(board, n, row, col, 'B', i, j);              
                                if (allowed == true) {
                                    validMoves[numValidMovesB][0] = (char)(row + 97);
                                    validMoves[numValidMovesB][1] = (char)(col + 97);
                                    numValidMovesB++;
                                }
                            }
                        }
                    }
                }
                
                if (tilesPlaced(board, n) == n * n) {
                    gameOver = true;
                } else if (numValidMovesB == 0) {
                    printf("B player has no valid move.\n");
                } else {
                    printf("Enter move for colour B (RowCol): ");
                    scanf(" %c%c", &row, &col);

                    valid = false;
                    for (int i = 0; i < numValidMovesB && valid == false; ++i) {
                        if (row == validMoves[i][0] && col == validMoves[i][1]) {
                            valid = true;
                        }
                    }

                    if (valid == true) {
                        for (int i = -1; i < 2; ++i) {
                            for (int j = -1; j < 2; ++j) {
                                swap(board, n, row - 97, col - 97, 'B', i, j);
                            }
                        }
                        updateBoard(board, n);
                    } else if (valid == false) {
                        printf("Invalid move.\n");
                        gameOver = true;
                    }
                }
            } else if (moveNumber % 2 == 1) {
                numValidMovesW = 0;
                for (int i = 0; i < n; ++i) {
                    for (int j = 0; j < n; ++j) {
                        scoreArray[i][j] = 0;
                    }
                }
                for (row = 0; row < n; ++row) {
                    for (col = 0; col < n; ++col) {
                        allowed = false;
                        for (int i = -1; i < 2 && allowed == false; ++i) {
                            for (int j = -1; j < 2 && allowed == false; ++j) { 
                                allowed = checkLegalInDirection(board, n, row, col, 'W', i, j);              
                                if (allowed == true) {
                                    validMoves[numValidMovesW][0] = (char)(row + 97);
                                    validMoves[numValidMovesW][1] = (char)(col + 97);
                                    numValidMovesW++;

                                }
                            }
                        }
                    }
                }
                
                for (int num = 0; num < numValidMovesW; ++num) {
                    for (int i = -1; i < 2; ++i) {
                        for (int j = -1; j < 2; ++j) {
                            moveScore(board, scoreArray, n, validMoves[num][0] - 97, validMoves[num][1] - 97, 'W', i, j);
                        }
                    }
                }

                if (tilesPlaced(board, n) == n * n) {
                    gameOver = true;
                } else if (numValidMovesW == 0) {
                    printf("W player has no valid move.\n");
                } else {
                    bestMove = 0;

                    for (int i = 0; i < n; ++i) {
                        for (int j = 0; j < n; ++j) {
                            if (scoreArray[i][j] > bestMove) {
                                bestMove = scoreArray[i][j];
                                bestMoveRow = i;
                                bestMoveCol = j;
                            }
                        }
                    }

                    printf("Computer places %c at %c%c.\n", compColour, (char)(bestMoveRow + 97), (char)(bestMoveCol + 97));
                    for (int i = -1; i < 2; ++i) {
                        for (int j = -1; j < 2; ++j) {
                            swap(board, n, bestMoveRow, bestMoveCol, 'W', i, j);
                        }
                    }
                    updateBoard(board, n);
                }
            }
            if (numValidMovesB == 0 && numValidMovesW == 0) {
                gameOver = true;

            }
        }
        
    } else if (compColour == 'B') {
        for (int moveNumber = 0; gameOver == false; ++moveNumber) {
            if (moveNumber % 2 == 1) {
                numValidMovesW = 0;                
                for (row = 0; row < n; ++row) {
                    for (col = 0; col < n; ++col) {
                        allowed = false;
                        for (int i = -1; i < 2 && allowed == false; ++i) {
                            for (int j = -1; j < 2 && allowed == false; ++j) { 
                                allowed = checkLegalInDirection(board, n, row, col, 'W', i, j);              
                                if (allowed == true) {
                                    validMoves[numValidMovesW][0] = (char)(row + 97);
                                    validMoves[numValidMovesW][1] = (char)(col + 97);
                                    numValidMovesW++;
                                }
                            }
                        }
                    }
                }
                if (tilesPlaced(board, n) == n * n) {
                    gameOver = true;
                } else if (numValidMovesW == 0) {
                    printf("W player has no valid move.\n");
                } else {
                    printf("Enter move for colour W (RowCol): ");
                    scanf(" %c%c", &row, &col);

                    valid = false;
                    for (int i = 0; i < numValidMovesW && valid == false; ++i) {
                        if (row == validMoves[i][0] && col == validMoves[i][1]) {
                            valid = true;
                        }
                    }

                    if (valid == true) {
                        for (int i = -1; i < 2; ++i) {
                            for (int j = -1; j < 2; ++j) {
                                swap(board, n, row - 97, col - 97, 'W', i, j);
                            }
                        }
                        updateBoard(board, n);
                    } else if (valid == false) {
                        printf("Invalid move.\n");
                        gameOver = true;
                    }
                }
            } else if (moveNumber % 2 == 0) {
                numValidMovesB = 0;
                for (int i = 0; i < n; ++i) {
                    for (int j = 0; j < n; ++j) {
                        scoreArray[i][j] = 0;
                    }
                }
                for (row = 0; row < n; ++row) {
                    for (col = 0; col < n; ++col) {
                        allowed = false;
                        for (int i = -1; i < 2 && allowed == false; ++i) {
                            for (int j = -1; j < 2 && allowed == false; ++j) { 
                                allowed = checkLegalInDirection(board, n, row, col, 'B', i, j);              
                                if (allowed == true) {
                                    validMoves[numValidMovesB][0] = (char)(row + 97);
                                    validMoves[numValidMovesB][1] = (char)(col + 97);
                                    numValidMovesB++;

                                }
                            }
                        }
                    }
                }
                               
                for (int num = 0; num < numValidMovesB; ++num) {
                    for (int i = -1; i < 2; ++i) {
                        for (int j = -1; j < 2; ++j) {
                            moveScore(board, scoreArray, n, validMoves[num][0] - 97, validMoves[num][1] - 97, 'B', i, j);
                        }
                    }
                }

                if (tilesPlaced(board, n) == n * n) {
                    gameOver = true;
                } else if (numValidMovesB == 0) {
                    printf("B player has no valid move.\n");
                } else {
                    bestMove = 0;

                    for (int i = 0; i < n; ++i) {
                        for (int j = 0; j < n; ++j) {
                            if (scoreArray[i][j] > bestMove) {
                                bestMove = scoreArray[i][j];
                                bestMoveRow = i;
                                bestMoveCol = j;
                            }
                        }
                    }

                    printf("Computer places %c at %c%c.\n", compColour, (char)(bestMoveRow + 97), (char)(bestMoveCol + 97));
                    for (int i = -1; i < 2; ++i) {
                        for (int j = -1; j < 2; ++j) {
                            swap(board, n, bestMoveRow, bestMoveCol, 'B', i, j);
                        }
                    }
                    updateBoard(board, n);
                }
            }
            
        }

    }

    if (gameOver == true) {
        int winner = doesBlackWin(board, n);
        if (winner == 1) {
            printf("B player wins.\n");
        } else if (winner == -1) {
            printf("W player wins.\n");
        } else if (winner == 0) {
            printf("Draw!\n");
        }
    }
    return 0;
}