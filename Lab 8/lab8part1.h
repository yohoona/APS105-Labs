//
// This is a header file for your Lab 7 solutions, which includes all
// the required function prototypes.
//
// Date: February 2024
//
// Please note: this file should not be modified.

#ifndef REVERSI_H
#define REVERSI_H

#include <stdbool.h>

// Function prototypes for Lab 7

void printBoard(char board[][26], int n);

bool positionInBounds(int n, int row, int col);

bool checkLegalInDirection(char board[][26], int n, int row, int col,
                           char colour, int deltaRow, int deltaCol);

#endif
