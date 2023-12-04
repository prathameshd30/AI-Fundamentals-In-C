#include <stdio.h>
#include <stdlib.h>

#define DIMENSION 3

int givenBoard[DIMENSION][DIMENSION];
int goalState[DIMENSION][DIMENSION] = {{1, 2, 3}, {8, 0, 4}, {7, 6, 5}};

void printBoard(int (*boardPos)[3])
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

void getBoardPosition(int (*board)[3])
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
        printBoard(board);
    }
}

void swapPos(int *a, int *b)
{
    int temp;
    temp = *a;
    *a = *b;
    *b = temp;
}

int heuristic_misplaced_tiles(int (*board)[3])
{
    int misplaced_tiles = 0;
    for (int i = 0; i < DIMENSION; ++i)
    {
        for (int j = 0; j < DIMENSION; ++j)
        {
            if (board[i][j] != goalState[i][j])
            {
                ++misplaced_tiles;
            }
        }
    }
    return misplaced_tiles / 2;
}

int main(void)
{
    int gapX, gapY;
    int tempBoard[DIMENSION][DIMENSION];

    printBoard(givenBoard);
    getBoardPosition(givenBoard);
    printf("This is the final board - \n");
    printBoard(givenBoard);
    int current_heuristic = heuristic_misplaced_tiles(givenBoard);
    int previous_heuristic = heuristic_misplaced_tiles(givenBoard);
    for (int i = 0; i < DIMENSION; ++i)
    {
        for (int j = 0; j < DIMENSION; ++j)
        {
            tempBoard[i][j] = givenBoard[i][j];
        }
    }
    previous_heuristic = heuristic_misplaced_tiles(tempBoard);
    for (int i = 0; i < DIMENSION; ++i)
    {
        for (int j = 0; j < DIMENSION; ++j)
        {
            if (tempBoard[i][j] == 0)
            {
                gapX = i;
                gapY = j;
            }
        }
    }
    if (gapX + 1 < DIMENSION)
    {
        swapPos(&(tempBoard[gapX][gapY]), &(tempBoard[gapX + 1][gapY]));
        current_heuristic = heuristic_misplaced_tiles(tempBoard);
        if (current_heuristic < previous_heuristic)
        {
            printf("Optimal move (not necessary most optimal) - \n");
            printBoard(tempBoard);
        }
        else
        {
            swapPos(&(tempBoard[gapX][gapY]), &(tempBoard[gapX + 1][gapY]));
        }
    }
    if (gapX - 1 > -1)
    {
        swapPos(&(tempBoard[gapX][gapY]), &(tempBoard[gapX - 1][gapY]));
        current_heuristic = heuristic_misplaced_tiles(tempBoard);
        if (current_heuristic < previous_heuristic)
        {
            printf("Optimal move (not necessary most optimal) - \n");
            printBoard(tempBoard);
        }
        else
        {
            swapPos(&(tempBoard[gapX][gapY]), &(tempBoard[gapX - 1][gapY]));
        }
    }
    if (gapY + 1 < DIMENSION)
    {
        swapPos(&(tempBoard[gapX][gapY]), &(tempBoard[gapX][gapY + 1]));
        current_heuristic = heuristic_misplaced_tiles(tempBoard);
        if (current_heuristic < previous_heuristic)
        {
            printf("Optimal move (not necessary most optimal) - \n");
            printBoard(tempBoard);
        }
        else
        {
            swapPos(&(tempBoard[gapX][gapY]), &(tempBoard[gapX][gapY + 1]));
        }
    }
    if (gapY - 1 > -1)
    {
        swapPos(&(tempBoard[gapX][gapY]), &(tempBoard[gapX][gapY - 1]));
        current_heuristic = heuristic_misplaced_tiles(tempBoard);
        if (current_heuristic < previous_heuristic)
        {
            printf("Optimal move (not necessary most optimal) - \n");
            printBoard(tempBoard);
        }
        else
        {
            swapPos(&(tempBoard[gapX][gapY]), &(tempBoard[gapX][gapY + 1]));
        }
    }
    printf("Final board\n");
    printBoard(tempBoard);
}