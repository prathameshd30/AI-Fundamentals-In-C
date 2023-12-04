#include <stdio.h>
#include <stdlib.h>

#define DIMENSION 3
#define MAX_MOVES 4
#define COST 1

int board[DIMENSION][DIMENSION];

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

void printBoardPos(int** boardPos)
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

void copyPos(int*** a,int index)
{
    for(int i = 0;i<DIMENSION;++i)
    {
        for(int j = 0;j<DIMENSION;++j)
        {
            a[index][i][j] = board[i][j];
        }
    }
}

int main(void)
{
    int possibleMoves;
    int gapX, gapY;
    initializeBoard();
    printBoard();
    getBoardPosition();
    printf("This is the final board - \n");
    printBoard();
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
    int*** possibleMovesPositions = (int***)calloc(MAX_MOVES,sizeof(int**));
    for (int i = 0; i < MAX_MOVES; i++)
    {
        possibleMovesPositions[i] = (int**)calloc(DIMENSION,sizeof(int*));
        for (int j = 0; j < DIMENSION; ++j)
        {
            possibleMovesPositions[i][j] = (int*)calloc(DIMENSION,sizeof(int));
        }
    }
    if (gapX + 1 < DIMENSION)
    {
        copyPos(possibleMovesPositions,possibleMoves);
        swapPos(&(possibleMovesPositions[possibleMoves][gapX][gapY]),&(possibleMovesPositions[possibleMoves][gapX+1][gapY]));
        ++possibleMoves;

    }
    if (gapX - 1 > -1)
    {
        copyPos(possibleMovesPositions,possibleMoves);
        swapPos(&(possibleMovesPositions[possibleMoves][gapX][gapY]),&(possibleMovesPositions[possibleMoves][gapX-1][gapY]));
        ++possibleMoves;
    }
    if (gapY + 1 < DIMENSION)
    {
        copyPos(possibleMovesPositions,possibleMoves);
        swapPos(&(possibleMovesPositions[possibleMoves][gapX][gapY]),&(possibleMovesPositions[possibleMoves][gapX][gapY+1]));
        ++possibleMoves;
    }
    if (gapY - 1 > -1)
    {
        copyPos(possibleMovesPositions,possibleMoves);
        swapPos(&(possibleMovesPositions[possibleMoves][gapX][gapY]),&(possibleMovesPositions[possibleMoves][gapX][gapY-1]));
        ++possibleMoves;
    }
    printf("Number of possible moves - %d\n", possibleMoves);
    possibleMovesPositions = realloc(possibleMovesPositions,possibleMoves*sizeof(int**));
    for(int i = 0;i<possibleMoves;++i)
    {
        printf("Move number - %d\n",i);
        printBoardPos(possibleMovesPositions[i]);
        printf("\n\n");
    }
    
}
