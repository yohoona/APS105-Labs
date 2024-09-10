#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

void readWordPuzzle(const int Size, char puzzle[][Size]);
char* readWord(int* wordSize);
void printWordPuzzle(const int Size, char puzzle[][Size]);
void printWord(char* word, const int wordSize);

void search(const int Size, char puzzle[][Size], const int wordSize, char* word);
bool inBounds(int row, int col, const int Size);

int main() {
    const int Size = 20;
    
    char puzzle[Size][Size];
    readWordPuzzle(Size, puzzle);
    int wordSize = 0;
    char* word = readWord(&wordSize);
    printWordPuzzle(Size, puzzle);

    printf("The word you are looking for is\n");
    printWord(word, wordSize);
    printf("\n");

    printf("Do you want to search? (Y or N)\n");
    char isSearch;
    scanf(" %c", &isSearch);

    if (isSearch == 'Y' || isSearch == 'y') {
        search(Size, puzzle, wordSize, word);
    }

    free(word);
    return 0;
}

void search(const int Size, char puzzle[][Size], const int wordSize, char* word) {
    int row, col;
    bool searchEast, searchWest, searchNorth, searchSouth, searchNE, searchNW, searchSE, searchSW;
    for (row = 0; row < Size; ++row) {
        for (col = 0; col < Size; ++col) {
            if (puzzle[row][col] == word[0]) {
                for (int i = 1; i < wordSize && searchEast == true; ++i) {
                    if (puzzle[row][col + i] == word[i]) {
                        searchEast = true;
                    } else {
                        searchEast = false;
                    }
                }
                for (int i = 1; i < wordSize && searchWest == true; ++i) {
                    if (puzzle[row][col - i] == word[i]) {
                        searchWest = true;
                    } else {
                        searchWest = false;
                    }                    
                }
                for (int i = 1; i < wordSize && searchNorth == true; ++i) {
                    if (puzzle[row + i][col] == word[i]) {
                        searchNorth = true;
                    } else {
                        searchNorth = false;
                    }
                for (int i = 1; i < wordSize && searchSouth == true; ++i) {
                    if (puzzle[row - i][col] == word[i]) {
                        searchNorth = true;
                    } else {
                        searchNorth = false;
                    }                    
                }
                for (int i = 1; i < wordSize && searchNE == true; ++i) {
                    if (puzzle[row + i][col + i] == word[i]) {
                        searchNE = true;
                    } else {
                        searchNE = false;
                    }                        
                }
                for (int i = 1; i < wordSize && searchNW == true; ++i) {
                    if (puzzle[row + i][col - i] == word[i]) {
                        searchNE = true;
                    } else {
                        searchNE = false;
                    }                        
                }
                for (int i = 1; i < wordSize && searchSE == true; ++i) {
                    if (puzzle[row - i][col + i] == word[i]) {
                        searchNE = true;
                    } else {
                        searchNE = false;
                    }                        
                }
                for (int i = 1; i < wordSize && searchSW == true; ++i) {
                    if (puzzle[row - i][col - i] == word[i]) {
                        searchNE = true;
                    } else {
                        searchNE = false;
                    }                        
                }
            }
        }
    }
}
    if (searchEast == true) {
        for (int i = 0; i < wordSize; ++i) {
            printf("%c", word[i]);
        }
        printf(" can be found at row , col = (%d, %d) in the east direction.", row, col);
    } else if (searchWest == true) {
                for (int i = 0; i < wordSize; ++i) {
            printf("%c", word[i]);
        }
        printf(" can be found at row , col = (%d, %d) in the west direction.", row, col);
    } else if (searchNorth == true) {
                for (int i = 0; i < wordSize; ++i) {
            printf("%c", word[i]);
        }
        printf(" can be found at row , col = (%d, %d) in the north direction.", row, col);
    } else if (searchSouth == true) {
                for (int i = 0; i < wordSize; ++i) {
            printf("%c", word[i]);
        }
        printf(" can be found at row , col = (%d, %d) in the south direction.", row, col);
    } else if (searchNE == true) {
                for (int i = 0; i < wordSize; ++i) {
            printf("%c", word[i]);
        }
        printf(" can be found at row , col = (%d, %d) in the north-east direction.", row, col);
    } else if (searchNW == true) {
                for (int i = 0; i < wordSize; ++i) {
            printf("%c", word[i]);
        }
        printf(" can be found at row , col = (%d, %d) in the north-west direction.", row, col);
    } else if (searchSE == true) {
                for (int i = 0; i < wordSize; ++i) {
            printf("%c", word[i]);
        }
        printf(" can be found at row , col = (%d, %d) in the south-east direction.", row, col);
    } else if (searchSW == true) {
                for (int i = 0; i < wordSize; ++i) {
            printf("%c", word[i]);
        }
        printf(" can be found at row , col = (%d, %d) in the south-west direction.", row, col);
    }
}

char* readWord(int* wordSize) {
    printf("How many characters are there in the word?\n");
    scanf("%d", *wordSize);
    int* word = (int*) malloc(sizeof(int) * *wordSize);

    printf("What is the word that you are looking for?\n");
    for (int i = 0; i < *wordSize; ++i) {
        scanf(" %c ", word[i]);
    }
}

/*char* readWord(int* wordSize) {
    printf("How many characters are there in the word?\n");
    scanf("%d", wordSize);
    int *word[*wordSize];
    printf("What is the word that you are looking for?\n");
    for (int i = 0; i < *wordSize; ++i) {
        word = malloc(sizeof(char) * *wordSize + 1);
        for (int j = 0; j < *wordSize; ++j) {
            scanf(" %c", word[i]);
        }
    }

}*/

void readWordPuzzle(const int Size, char puzzle[][Size]) {
    char letter;
    printf("Please enter the word puzzle:\n");
    for (int rows = 0; rows < Size; ++rows) {
        for (int cols = 0; cols < Size; ++cols) {
            scanf(" %c", &letter);
            letter = puzzle[rows][cols];
        }
    }
}

bool inBounds(int row, int col, const int Size) {
    bool itsInsideMe = false;
    if (row <= Size && col <= Size) {
        itsInsideMe = true;
    }
    return itsInsideMe;
}

void printWordPuzzle(const int Size, char puzzle[][Size]) {
    for (int rows = 0; rows < Size; ++rows) {
        for(int cols = 0; cols < Size; ++cols) {
            printf(" %c ", puzzle[rows][cols]);
        }
        printf("\n");
    }
}

void printWord(char* word, const int wordSize) {
    for (int i = 0; i < wordSize; ++i) {
        printf(" %c", word[i]);
    }
}