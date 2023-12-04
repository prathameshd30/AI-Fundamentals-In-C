#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define DIMENSION 3
#define MAX_MOVES 4

int board[DIMENSION][DIMENSION];
int goalState[DIMENSION][DIMENSION] = {{1, 2, 3}, {8, 0, 4}, {7, 6, 5}};
void initializeBoard(void)
{
    for (int i = 0; i < DIMENSION; ++i)
    {
        for (int j = 0; j < DIMENSION; ++j)
        {
            board[i][j] = 0;
        }
    }
}

void printGoalBoard(void)
{
    for (int i = 0; i < DIMENSION; ++i)
    {
        printf("-------------\n");
        for (int j = 0; j < DIMENSION; ++j)
        {
            printf("|");
            if (goalState[i][j] == 0)
            {
                printf("   ");
            }
            else
            {
                printf(" %d ", goalState[i][j]);
            }
        }
        printf("|\n");
    }
    printf("-------------\n");
}

void printBoard(void)
{
    for (int i = 0; i < DIMENSION; ++i)
    {
        printf("-------------\n");
        for (int j = 0; j < DIMENSION; ++j)
        {
            printf("|");
            if (board[i][j] == 0)
            {
                printf("   ");
            }
            else
            {
                printf(" %d ", board[i][j]);
            }
        }
        printf("|\n");
    }
    printf("-------------\n");
}

void printBoardPos(int **boardPos)
{
    for (int i = 0; i < DIMENSION; ++i)
    {
        printf("-------------\n");
        for (int j = 0; j < DIMENSION; ++j)
        {
            printf("|");
            if (boardPos[i][j] == 0)
            {
                printf("   ");
            }
            else
            {
                printf(" %d ", boardPos[i][j]);
            }
        }
        printf("|\n");
    }
    printf("-------------\n");
}

void getBoardPosition(void)
{
    int xCoord, yCoord;
    for (int i = 1; i < DIMENSION * DIMENSION; ++i)
    {
        printf("Please enter cell position for %d\n", i);
        scanf("%d %d", &xCoord, &yCoord);
        if (xCoord > -1 && xCoord < 3 && yCoord > -1 && yCoord < 3)
        {
            board[xCoord][yCoord] = i;
        }
        printBoard();
    }
}

void swapPos(int *a, int *b)
{
    int temp;
    temp = *a;
    *a = *b;
    *b = temp;
}

int heuristic_misplaced_tiles(int **position)
{
    int misplacedTiles = 0;
    for (int i = 0; i < DIMENSION; ++i)
    {
        for (int j = 0; j < DIMENSION; ++j)
        {
            if (position[i][j] != goalState[i][j])
            {
                ++misplacedTiles;
            }
        }
    }
    return misplacedTiles / 2;
}

void copyPos(int ***a, int index)
{
    for (int i = 0; i < DIMENSION; ++i)
    {
        for (int j = 0; j < DIMENSION; ++j)
        {
            a[index][i][j] = board[i][j];
        }
    }
}

int main(void)
{
    int possibleMoves;
    int gapX, gapY;
    int minHeuristic = 9;
    initializeBoard();
    printBoard();
    getBoardPosition();
    printf("This is the final board - \n");
    printBoard();
    while (minHeuristic != 0)
    {
        for (int i = 0; i < DIMENSION; ++i)
        {
            for (int j = 0; j < DIMENSION; ++j)
            {
                if (board[i][j] == 0)
                {
                    gapX = i;
                    gapY = j;
                }
            }
        }
        possibleMoves = 0;
        int ***possibleMovesPositions = (int ***)calloc(MAX_MOVES, sizeof(int **));
        for (int i = 0; i < MAX_MOVES; i++)
        {
            possibleMovesPositions[i] = (int **)calloc(DIMENSION, sizeof(int *));
            for (int j = 0; j < DIMENSION; ++j)
            {
                possibleMovesPositions[i][j] = (int *)calloc(DIMENSION, sizeof(int));
            }
        }
        if (gapX + 1 < DIMENSION)
        {
            copyPos(possibleMovesPositions, possibleMoves);
            swapPos(&(possibleMovesPositions[possibleMoves][gapX][gapY]), &(possibleMovesPositions[possibleMoves][gapX + 1][gapY]));
            ++possibleMoves;
        }
        if (gapX - 1 > -1)
        {
            copyPos(possibleMovesPositions, possibleMoves);
            swapPos(&(possibleMovesPositions[possibleMoves][gapX][gapY]), &(possibleMovesPositions[possibleMoves][gapX - 1][gapY]));
            ++possibleMoves;
        }
        if (gapY + 1 < DIMENSION)
        {
            copyPos(possibleMovesPositions, possibleMoves);
            swapPos(&(possibleMovesPositions[possibleMoves][gapX][gapY]), &(possibleMovesPositions[possibleMoves][gapX][gapY + 1]));
            ++possibleMoves;
        }
        if (gapY - 1 > -1)
        {
            copyPos(possibleMovesPositions, possibleMoves);
            swapPos(&(possibleMovesPositions[possibleMoves][gapX][gapY]), &(possibleMovesPositions[possibleMoves][gapX][gapY - 1]));
            ++possibleMoves;
        }
        printf("Number of possible moves - %d\n", possibleMoves);
        possibleMovesPositions = realloc(possibleMovesPositions, possibleMoves * sizeof(int **));
        int *possibleMovesScores = (int *)calloc(possibleMoves, sizeof(int));
        printGoalBoard();
        minHeuristic = 10;
        int minHeuristicIndex = -1;
        for (int i = 0; i < possibleMoves; ++i)
        {
            printf("Move number - %d\n", i);
            possibleMovesScores[i] = heuristic_misplaced_tiles(possibleMovesPositions[i]);
            if (possibleMovesScores[i] < minHeuristic)
            {
                minHeuristic = possibleMovesScores[i];
                minHeuristicIndex = i;
            }
            printBoardPos(possibleMovesPositions[i]);
            printf("\nScore - %d", possibleMovesScores[i]);
            printf("\n\n");
        }
        if (minHeuristic == 10)
        {
            printf("Stuck\n");
            
            return 0;
        }
        else
        {
            printf("Thus best move with score %d is - \n", minHeuristic);
            printBoardPos(possibleMovesPositions[minHeuristicIndex]);
        }
        printf("Executing best move\n");
        for (int i = 0; i < DIMENSION; ++i)
        {
            for (int j = 0; j < DIMENSION; ++j)
            {
                board[i][j] = possibleMovesPositions[minHeuristicIndex][i][j];
            }
        }
        printBoard();
    }
}
