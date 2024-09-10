#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <math.h>

typedef struct mctsNode {
    char algoColour;
    int previousMove;
    struct mctsNode* parent;
    struct mctsNode* child[676];
    int childCount;
    int nodeVisits;
    double nodeScore;
    int unvisitedNodes;
} mctsNode;

void createBoard(char board[][26], int n) {
    for (int row = 0; row < n; ++row) {
        for (int col = 0; col < n; ++col) {
            if ((row == n / 2 - 1 && col == n / 2 - 1) || (row == n / 2 && col == n / 2)) {
                    board[row][col] = 'W';
                } else if ((row == n / 2 - 1 && col == n / 2) || (row == n / 2 && col == n / 2 - 1)) {
                    board[row][col] = 'B';
                } else {
                    board[row][col] = 'U';
                }
        }
    }
}
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
int whoWins(char board[][26], int n) {
        int blackTiles = 0;
        int whiteTiles = 0;
        int winner;
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
            winner = 1;
        } else if (blackTiles < whiteTiles) {
            winner = -1;
        } else if (blackTiles == whiteTiles) {
            winner = 0;
        }

        return winner;

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
int legalMoves(char board[][26], int validMoves[][2], int n, char colour) {
    bool validMove;
    int validMoveCount = 0;
    for (int row = 0; row < n; ++row) {
        for (int col = 0; col < n; ++col) {
            validMove = false;
            for (int i = -1; i < 2 && validMove == false; ++i) {
                for (int j = -1; j < 2 && validMove == false; ++j) {
                    validMove = checkLegalInDirection(board, n, row, col, colour, i, j);
                    
                    if (validMove == true) {
                        validMoves[validMoveCount][0] = row;
                        validMoves[validMoveCount][1] = col;
                        validMoveCount++;
                    }
                    
                }
            }
        }
    }
    return validMoveCount;
}
double gameScore(char board[][26], int n, char colour) {
    int myTiles = 0;
    int oppTiles = 0;
    int score;
    for (int row = 0; row < n; ++row) {
        for (int col = 0; col < n; ++col) {
            if (board[row][col] == colour) {
                myTiles++;
            } else if (board[row][col] != colour && board[row][col] != 'U') {
                oppTiles++;
            }
        }
    }
    if (myTiles > oppTiles) {
        score = 1;
    } else if (myTiles < oppTiles) {
        score = 0;
    } else if (myTiles == oppTiles) {
        score = 0.5;
    }
    return score;
}
bool gameOver(char board[][26], int validMoves[][2], int n) {
    bool isTheGameOver = false;
    if (legalMoves(board, validMoves, n, 'B') == 0 && legalMoves(board, validMoves, n, 'W') == 0) {
        isTheGameOver = true;
    }
    return isTheGameOver;
}
char swapTurns(int moveCount) {
    char colourTurn;
    if (moveCount % 2 == 0) {
        colourTurn = 'B';
    } else if (moveCount % 2 == 1) {
        colourTurn = 'W';
    }
    return colourTurn;
}

/*void updateValidMoves(char board[][26], int validMoves[][2], int n, char colour) {
    bool validMove;
    int numValidMoves = 0;
    for (int row = 0; row < n; ++row) {
        for (int col = 0; col < n; ++col) {
            validMove = false;
            for (int i = -1; i < 2 && validMove == false; ++i) {
                for (int j = -1; j < 2 && validMove == false; ++j) {
                    if (checkLegalInDirection(board, n, row, col, colour, i, j) == true) {
                        validMove = checkLegalInDirection(board, n, row, col, colour, i, j);
                        validMoves[numValidMoves][0] = row;
                        validMoves[numValidMoves][1] = col;
                        numValidMoves++; 
                    }
                }
            }
        }
    }
}*/

mctsNode* createNode(mctsNode* parent, const char board[][26], int validMoves[][2], int n, char colour) {
    mctsNode* node = (mctsNode*)malloc(sizeof(mctsNode*));
    node->algoColour = colour;
    node->previousMove = 0;
    node->parent = parent;
    node->childCount = 0;
    node->nodeVisits = 0;
    node->nodeScore = 0.0;
    node->unvisitedNodes = legalMoves(board, validMoves, n, colour);
    return node;
}

mctsNode* selectChildNode(mctsNode* node) {
    mctsNode* selectedNode = NULL;
    double highestScore = -INFINITY;
    for (int i = 0; i < node->childCount; ++i) {
        mctsNode* childNode = node->child[i];
        double nodeUCT = childNode->nodeScore / childNode->nodeVisits + sqrt(2 * log(node->nodeVisits) / childNode->nodeVisits);

        if (nodeUCT > highestScore) {
            nodeUCT = highestScore;
            selectedNode = childNode;
        } 
    }
    return selectedNode;
}

void generateChildNodes(mctsNode* node, char board[][26], int validMoves[][2], int n) {
    for (int i = 0; i < node->childCount; ++i) { //fix
        if (node->algoColour = 'W') {
            mctsNode* newborn = createNode(node, board, validMoves, n, 'B');
            newborn = node->child[i];
        } else {
            mctsNode* newborn = createNode(node, board, validMoves, n, 'W');
            newborn = node->child[i];
        }
    }
}

double simulateGame(char board[][26], int validMoves[][2], int n, char colour) {
    int moveRow;
    int moveCol;
    bool isGameOver = false;
    bool validMove;
    for (int moveCount = 0; isGameOver == false; ++moveCount) {
        char currentPlayer = swapTurns(moveCount);
        int legalMoveCount = legalMoves(board, validMoves, n, currentPlayer);
        isGameOver = gameOver(board, validMoves, n);
        if (colour == currentPlayer && isGameOver == false) {
            moveRow = validMoves[rand() % legalMoveCount][0];
            moveCol = validMoves[rand() % legalMoveCount][1];
            for (int i = -1; i < 2; ++i) {
                for (int j = -1; j < 2; ++j) {
                    swap(board, n, moveRow, moveCol, colour, i, j);
                }
            }
        } else if (colour != currentPlayer && isGameOver == false) {
            //findSmartestMove(board, n, currentPlayer, &row, &col);
            moveRow = validMoves[rand() % legalMoveCount][0];
            moveCol = validMoves[rand() % legalMoveCount][1];
        }
    }
    double result = gameScore(board, n, colour);
    return result;
}

void backpropagate(mctsNode* node, double result) {
    while (node != NULL) {
        node->nodeVisits++;
        node->nodeScore += result;
        node = node->parent;
    }
}

void makeAMove(char board[][26], int validMoves[][2], int n, char colour) {

}


//kind of unclear on this part
mctsNode* mcts(char board[][26], int validMoves[][2], int n, int colour, int iterations) {
    mctsNode* rootNode = createNode(NULL, board, validMoves, n, colour);
    for (int i = 0; i < iterations; ++i) {
        mctsNode* nodeToBeExplored = rootNode;
        
        while (nodeToBeExplored->childCount > 0) {
            nodeToBeExplored = selectChildNode(rootNode);    
        }

        if (nodeToBeExplored->nodeVisits != 0) {
            generateChildNodes(nodeToBeExplored, board, validMoves, n);
            nodeToBeExplored = nodeToBeExplored->child[rand() % nodeToBeExplored->childCount];
        }

        double simulationResult = simulateGame(board, validMoves, n, nodeToBeExplored->algoColour);

        backpropagate(nodeToBeExplored, simulationResult);
    }

    return rootNode;
}


int makeMove(const char board[][26], int n, char turn, int *row, int *col) {
    /*bool allowed;
    int validMovesW[n * n][2];
    int validMovesB[n * n][2];
    int numValidMovesW = 0;
    int numValidMovesB = 0;
    if (turn == 'B') {
        for (int row = 0; row < n; ++row) {
            for (int col = 0; col < n; ++col) {
                allowed = false;
                for (int i = -1; i < 2 && allowed == false; ++i) {
                    for (int j = -1; j < 2 && allowed == false; ++j) { 
                        allowed = checkLegalInDirection(board, n, row, col, 'B', i, j);              
                        if (allowed == true) {
                            validMovesB[numValidMovesB][0] = row;
                            validMovesB[numValidMovesB][1] = col;
                            numValidMovesB++;
                        }
                    }
                }
            }
        }
    } else if (turn == 'W') {
        for (int row = 0; row < n; ++row) {
            for (int col = 0; col < n; ++col) {
                allowed = false;
                for (int i = -1; i < 2 && allowed == false; ++i) {
                    for (int j = -1; j < 2 && allowed == false; ++j) { 
                        allowed = checkLegalInDirection(board, n, row, col, 'B', i, j);              
                        if (allowed == true) {
                            validMovesW[numValidMovesW][0] = row;
                            validMovesW[numValidMovesW][1] = col;
                            numValidMovesW++;
                        }
                    }
                }
            }
        }
    }
*/
    
}