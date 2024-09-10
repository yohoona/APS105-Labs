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
    int moveScore(char board[][26], int n, int row, int col, char colour, int deltaRow, int deltaCol) {
        bool isSameColour = false;
        int numTilesFlipped = 0;
        for (int i = 2; row + (i - 1) * deltaRow >= 0 && row + (i - 1) * deltaRow < n && col + (i - 1) * deltaCol >= 0 && col + (i - 1) * deltaCol < n && isSameColour == false && board[row + (i - 1) * deltaRow][col + (i - 1) * deltaCol] != 'U' && board[row + (i - 1) * deltaRow][col + (i - 1) * deltaCol] != colour; i++) {
            if (board[row + i * deltaRow][col + i * deltaCol] == colour) {
                isSameColour = true;
                for (int j = 1; j < i; ++j) {
                    numTilesFlipped++;
                }
            }             
        }
        return numTilesFlipped;
    }  
    int legalMoves(char board[][26], int validMoves[][3], int n, char colour) {
        bool legalMove;
        int legalMoveCount = 0;
        int scoreOfMove;
        for (int row = 0; row < n; ++row) {
            for (int col = 0; col < n; ++col) {
                scoreOfMove = 0;
                legalMove = false;
                for (int i = -1; i < 2 && legalMove == false; ++i) {
                    for (int j = -1; j < 2 && legalMove == false; ++j) {
                        legalMove = checkLegalInDirection(board, n, row, col, colour, i, j);                      
                    }
                }
                if (legalMove == true) {
                    for (int i = -1; i < 2; ++i) {
                        for (int j = -1; j < 2; ++j) {
                            scoreOfMove += moveScore(board, n, row, col, colour, i, j);
                        }
                    }
                    validMoves[legalMoveCount][0] = row;
                    validMoves[legalMoveCount][1] = col;
                    validMoves[legalMoveCount][2] = scoreOfMove;
                    legalMoveCount++;
                }               
            }
        }
        return legalMoveCount;
    }
    int tileCount(char board[][26], int n) {
        int numTiles = 0;
        for (int row = 0; row < n; ++row) {
            for (int col = 0; col < n; ++col) {
                if (board[row][col] != 'U') {
                    numTiles++;
                }
            }
        }
        return numTiles;
    }
    int whoWins(char board[][26], int n) {
        int winner;
        int blackTiles = 0;
        int whiteTiles = 0;
        for (int row = 0; row < n; ++row) {
            for (int col = 0; col < n; ++col) {
                if (board[row][col] == 'B') {
                    blackTiles++;
                } else if (board[row][col] == 'W') {
                    whiteTiles++;
                }
            }
        }

        if (blackTiles > whiteTiles) {
            winner = 1;
        } else if (blackTiles < whiteTiles) {
            winner = -1;
        } else if (blackTiles == whiteTiles) {
            winner = 0;
        }
        return winner;
    }
    bool gameOver(char board[][26], int validMoves[][3], int n) {
        bool isTheGameOver = false;
        if (legalMoves(board, validMoves, n, 'B') == 0 && legalMoves(board, validMoves, n, 'W') == 0) {
            isTheGameOver = true;
        } else if (tileCount(board, n) == n * n) {
            isTheGameOver = true;
        }
        return isTheGameOver;
    }
    char whoseTurn(int moveCount) {
        char colourTurn;
        if (moveCount % 2 == 0) {
            colourTurn = 'B';
        } else if (moveCount % 2 == 1) {
            colourTurn = 'W';
        }
        return colourTurn;
    }
    void computerPlayMove(char board[][26], int validMoves[][3], int n, char colour) {
        int largestMoveScore = 0;
        int moveIndex;
        int legalMoveCount = legalMoves(board, validMoves, n, colour);
        
        //why tf is it reversed?
        for (int i = legalMoveCount; i > 0; --i) {
            if (validMoves[i - 1][2] > largestMoveScore) {
                validMoves[i - 1][2] = largestMoveScore;
                moveIndex = i - 1;
            }
        }

        if (largestMoveScore = 0) {
            printf("%c player has no valid move.", colour);
        } else {
            for (int i = -1; i < 2; ++i) {
                for (int j = -1; j < 2; ++j) {
                    swap(board, n, validMoves[moveIndex][0], validMoves[moveIndex][1], colour, i, j);
                }
            }
            printf("Computer places %c at %c%c.\n", colour, (char)(validMoves[moveIndex][0] + 97), (char)(validMoves[moveIndex][1] + 97));
        }
    }

int main() {
    int n;
    char board[26][26];
    int validMoves[676][3];

    printf("Enter the board dimension: ");
    scanf(" %d", &n);

    char computerColour;
    printf("Computer plays (B/W): ");
    scanf(" %c", &computerColour);

    printBoard(board, n);

    bool isGameOver = false;
    bool lossByInvalidMove = false;
    char winner;
    char toMove;
    for (int i = 0; isGameOver == false && lossByInvalidMove == false; ++i) {
        isGameOver = gameOver(board, validMoves, n); 

        toMove = whoseTurn(i);

        //print statements to test code
        //printf("\n%c's move, possible moves:\n", toMove);

        int legalMoveCount = legalMoves(board, validMoves, n, toMove);

       /*for (int i = 0; i < legalMoveCount; ++i) {
            printf("%c%c (score: %d) ", (char)(validMoves[i][0] + 97), (char)(validMoves[i][1] + 97), validMoves[i][2]);
        }
        printf("\n\n");*/
        //end of print statments

        if (toMove == computerColour && isGameOver == false) {
            if (legalMoveCount > 0) {
                computerPlayMove(board, validMoves, n, computerColour);
                updateBoard(board, n);
            } else {
                printf("%c player has no valid move.\n", toMove);
            }
            
        } else if (toMove != computerColour && isGameOver == false) {
            if (legalMoveCount > 0) {
                char moveRow, moveCol;
                printf("Enter move for colour %c (RowCol): ", toMove);
                scanf(" %c%c", &moveRow, &moveCol);

                bool isLegalMove = false;
                for (int i = 0; i < legalMoveCount && isLegalMove == false; ++i) {
                    if (validMoves[i][0] == (int)(moveRow - 97) && validMoves[i][1] == (int)(moveCol - 97)) {
                        isLegalMove = true;
                    }
                }
                if (isLegalMove == false) {
                    printf("Invalid move.\n");
                    lossByInvalidMove = true;
                    winner = whoseTurn(i + 1);
                } else {
                    for (int i = -1; i < 2; ++i) {
                        for (int j = -1; j < 2; ++j) {
                            swap(board, n, (int)(moveRow - 97), (int)(moveCol - 97), toMove, i, j);
                        }
                    }
                    updateBoard(board, n);
                }
            } else {
                printf("%c player has no valid move.\n", toMove);
            }
        }
    }
    
    if (lossByInvalidMove == true) {
        printf("%c player wins.\n", winner);
    } else if (whoWins(board, n) == 1) {
        printf("B player wins.\n");
    } else if (whoWins(board, n) == -1) {
        printf("W player wins.\n");
    } else if (whoWins(board, n) == 0) {
        printf("Draw!\n");
    }

    return 0;
}