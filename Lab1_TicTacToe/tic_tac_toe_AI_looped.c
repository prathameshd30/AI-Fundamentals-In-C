#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#define SIZE 3

#define CENTER_SCORE 4
#define CORNER_SCORE 3
#define EDGE_SCORE 2

#define WINNING_MOVE_SCORE 100
#define BLOCKING_MOVE_SCORE 50

void printBoard(int (*board)[SIZE], int size)
{
    for (unsigned short i = 0; i < size; ++i)
    {
        printf("-------------\n");
        for (unsigned short j = 0; j < size; ++j)
        {
            printf("|");
            switch (board[i][j])
            {
            case 0:
                printf("%d %d", i, j);
                break;
            case 1:
                printf(" X ");
                break;
            case 2:
                printf(" O ");
                break;
            default:
                break;
            }
        }
        printf("|\n");
    }
    printf("-------------\n");
}

void getBoardState(int (*boardPos)[SIZE], int size)
{
    char action;
    int xcoord, ycoord;
    int choice;
    do
    {
        printBoard(boardPos, size);
        puts("Please select 1 to modify cell (0 to submit board)");
        scanf(" %c", &action);
        if (action == '0')
        {
            return;
        }
        printf("Please enter 1st coordinate of cell to change\n");
        scanf(" %d", &xcoord);
        printf("Please enter 2nd coordinate of cell to change\n");
        scanf(" %d", &ycoord);
        printf("Please enter choice of character\n1\tX\n2\tO\n");
        scanf(" %d", &choice);
        if (choice >= 1 && choice < size && xcoord >= 0 && xcoord < size && ycoord >= 0 && ycoord < size)
        {
            boardPos[xcoord][ycoord] = choice;
        }
        else
        {
            printf("Invalid move\n");
        }
    } while (action != '0');
}

bool winningCheck(int *board)
{
    if ((board[0] == board[1] && board[1] == board[2] && board[0] != 0) ||
        (board[3] == board[4] && board[4] == board[5] && board[3] != 0) ||
        (board[6] == board[7] && board[7] == board[8] && board[6] != 0))
        return 1;

    if ((board[0] == board[3] && board[3] == board[6] && board[0] != 0) ||
        (board[1] == board[4] && board[4] == board[7] && board[1] != 0) ||
        (board[2] == board[5] && board[5] == board[8] && board[2] != 0))
        return 1;

    if ((board[0] == board[4] && board[4] == board[8] && board[0] != 0) ||
        (board[2] == board[4] && board[4] == board[6] && board[2] != 0))
        return 1;

    return 0;
}

int isWinningMove(int *tempBoard, int move, int player)
{
    char original = tempBoard[move];
    tempBoard[move] = player;
    int result = winningCheck(tempBoard);
    tempBoard[move] = original;
    return result;
}

int isBlockingMove(int *tempBoard, int move, int player)
{
    int opponent = (player == 1) ? 2 : 1;
    int original = tempBoard[move];
    tempBoard[move] = opponent;
    int result = winningCheck(tempBoard);
    tempBoard[move] = original;
    return result;
}

int main(void)
{
    int originalBoard[SIZE][SIZE];
    int vector[SIZE * SIZE];
    memset(originalBoard, 0, sizeof(originalBoard));
    getBoardState(originalBoard, SIZE);
    printBoard(originalBoard, SIZE);
    int firstPlayer;
    printf("Please enter who played first\n1\tX\n2\tO\n");
    scanf(" %d", &firstPlayer);

    int tempBoard[SIZE][SIZE];
    for (int i = 0; i < SIZE; ++i)
    {
        for (int j = 0; j < SIZE; ++j)
        {
            tempBoard[i][j] = originalBoard[i][j];
        }
    }
    for (int i = 0; i < SIZE; ++i)
    {
        for (int j = 0; j < SIZE; ++j)
        {
            vector[3 * i + j] = tempBoard[i][j];
        }
    }

    while (!winningCheck(vector))
    {
        int xcount = 0;
        int ycount = 0;
        for (unsigned short i = 0; i < SIZE * SIZE; ++i)
        {
            if (vector[i] == 1)
            {
                ++xcount;
            }
            else if (vector[i] == 2)
            {
                ++ycount;
            }
        }
        if (firstPlayer == 1)
        {
            if (xcount - ycount > 1 || xcount - ycount < 0)
            {
                printf("Invalid configuration\n");
                return 0;
            }
        }
        else if (firstPlayer == 2)
        {
            if (ycount - xcount > 1 || ycount - xcount < 0)
            {
                printf("Invalid configuration\n");
                return 0;
            }
        }
        printf("\nVector is - ");
        for (int i = 0; i < SIZE * SIZE; i++)
        {
            printf(" %d", vector[i]);
        }
        int index = 0;
        for (int i = 0; i < SIZE * SIZE; ++i)
        {
            int numToBeMultiplied = 1;
            for (int j = 0; j < i; j++)
            {
                numToBeMultiplied *= 3;
            }

            index += vector[(SIZE * SIZE - 1) - i] * numToBeMultiplied;
        }
        printf("\nIndex of this rule is - %llu\n", index);
        int playerToMove;
        if (winningCheck(vector) == 1)
        {
            printf("\nThis board is already in winning,thus no next move is possible\n");
            return 0;
        }
        if (xcount - ycount == 0)
        {
            printf("As Xs and Os are equal, the first player has their turn\n");
            playerToMove = firstPlayer;
        }
        else
        {
            printf("As Xs and Os are unequal, the second player has their turn");
            if (firstPlayer == 1)
            {
                playerToMove = 2;
            }
            else
            {
                playerToMove = 1;
            }
        }
        unsigned short zeroCounter = 0;
        for (int i = 0; i < SIZE * SIZE; ++i)
        {
            if (vector[i] == 0)
            {
                ++zeroCounter;
            }
        }
        if(zeroCounter == 0)
        {
            printf("\nGame is over\n");
            return 0;
        }
        int **moveMatrix = (int **)calloc(zeroCounter, sizeof(int *));
        for (int i = 0; i < zeroCounter; ++i)
        {
            moveMatrix[i] = (int *)calloc(SIZE * SIZE, sizeof(int));
        }
        for (int i = 0; i < zeroCounter; ++i)
        {
            for (int j = 0; j < SIZE * SIZE; ++j)
            {
                moveMatrix[i][j] = vector[j];
            }
        }
        int tempZeroIndex = -1;
        int *scoreVector = (int *)calloc(zeroCounter, sizeof(int));
        int *changedIndex = (int *)calloc(zeroCounter, sizeof(int));
        for (int i = 0; i < zeroCounter; ++i)
        {
            for (int j = 0; j < SIZE * SIZE; ++j)
            {
                if (moveMatrix[i][j] == 0 && j > tempZeroIndex)
                {
                    moveMatrix[i][j] = playerToMove;
                    tempZeroIndex = j;
                    changedIndex[i] = j;
                    break;
                }
            }
        }
        printf("\nMove matrix is -\n");
        for (int i = 0; i < zeroCounter; ++i)
        {

            for (int j = 0; j < SIZE * SIZE; ++j)
            {
                printf("%d ", moveMatrix[i][j]);
                if ((j + 1) % 3 == 0)
                {
                    printf("\n");
                }
            }
            printf("\n");
            if (isWinningMove(moveMatrix[i], changedIndex[i], moveMatrix[i][changedIndex[i]]))
            {
                scoreVector[i] = WINNING_MOVE_SCORE;
                continue;
            }
            else if (isBlockingMove(moveMatrix[i], changedIndex[i], moveMatrix[i][changedIndex[i]]))
            {
                scoreVector[i] = BLOCKING_MOVE_SCORE;
                continue;
            }
            else if (changedIndex[i] == 0 || changedIndex[i] == 2 ||
                     changedIndex[i] == 6 || changedIndex[i] == 8)
            {
                scoreVector[i] = CORNER_SCORE;
                continue;
            }
            else if (changedIndex[i] == 1 || changedIndex[i] == 3 || changedIndex[i] == 5 || changedIndex[i] == 7)
            {
                scoreVector[i] = EDGE_SCORE;
                continue;
            }
            else if (changedIndex[i] == 4)
            {
                scoreVector[i] = CENTER_SCORE;
                continue;
            }
        }
        int maxScore = 0;
        int maxScoreIndex;
        for (int i = 0; i < zeroCounter; ++i)
        {
            for (int j = 0; j < SIZE * SIZE; ++j)
            {
                printf("%d ", moveMatrix[i][j]);
            }
            if (scoreVector[i] > maxScore)
            {
                maxScore = scoreVector[i];
                maxScoreIndex = i;
            }
            printf("- %d\n", scoreVector[i]);
        }
        printf("Hence, the best move is - ");
        for (int i = 0; i < SIZE * SIZE; ++i)
        {
            printf("%d ", moveMatrix[maxScoreIndex][i]);
        }
        printf("with score - %d\n", scoreVector[maxScoreIndex]);
        printf("Executing this as latest move\n");
        for (int i = 0; i < SIZE * SIZE; ++i)
        {
            vector[i] = moveMatrix[maxScoreIndex][i];
        }
        
        for (int i = 0; i < zeroCounter; ++i)
        {
            free(moveMatrix[i]);
        }
        free(moveMatrix);
        free(scoreVector);
        free(changedIndex);
    }

}