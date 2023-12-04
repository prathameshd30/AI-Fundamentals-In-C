#include <stdio.h>
#include <stdlib.h>
#define DIMENSION 3
#define WINNING_MOVE_SCORE 100
#define BLOCKING_MOVE_SCORE 50
#define CENTER_SCORE 4
#define EDGE_SCORE 2
#define CORNER_SCORE 3
unsigned short board[DIMENSION][DIMENSION];
int vector[DIMENSION*DIMENSION];
void initializeBoard(void)
{
    for(unsigned short i = 0; i<DIMENSION;++i)
    {
        for(unsigned short j = 0; j<DIMENSION;++j)
        {
            board[i][j] = 0;
        }
    }
}

void printBoard()
{
    for(unsigned short i = 0; i< DIMENSION;++i)
    {
        printf("-------------\n");
        for(unsigned short j = 0; j<DIMENSION;++j)
        {
            printf("|");
            switch (board[i][j])
            {
            case 0:
                printf("%d %d",i,j);
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


int winningCheck(int* tempBoard) {
    if ((tempBoard[0] == tempBoard[1] && tempBoard[1] == tempBoard[2] && tempBoard[0] != 0) ||
        (tempBoard[3] == tempBoard[4] && tempBoard[4] == tempBoard[5] && tempBoard[3] != 0) ||
        (tempBoard[6] == tempBoard[7] && tempBoard[7] == tempBoard[8] && tempBoard[6] != 0))
        return 1;

    if ((tempBoard[0] == tempBoard[3] && tempBoard[3] == tempBoard[6] && tempBoard[0] != 0) ||
        (tempBoard[1] == tempBoard[4] && tempBoard[4] == tempBoard[7] && tempBoard[1] != 0) ||
        (tempBoard[2] == tempBoard[5] && tempBoard[5] == tempBoard[8] && tempBoard[2] != 0))
        return 1;

    if ((tempBoard[0] == tempBoard[4] && tempBoard[4] == tempBoard[8] && tempBoard[0] != 0) ||
        (tempBoard[2] == tempBoard[4] && tempBoard[4] == tempBoard[6] && tempBoard[2] != 0))
        return 1;

    return 0;
}


int isWinningMove(int* tempBoard, int move, int player) {
    char original = tempBoard[move];
    tempBoard[move] = player;
    int result = winningCheck(tempBoard);
    tempBoard[move] = original;
    return result;
}

int isBlockingMove(int* tempBoard,int move, int player) {
    int opponent = (player == 1) ? 2 : 1;
    int original = tempBoard[move];
    tempBoard[move] = opponent;
    int result = winningCheck(tempBoard);
    tempBoard[move] = original;
    return result;
}

int main(void)
{
    initializeBoard();
    
    unsigned short action;
    unsigned short xcoord;
    unsigned short ycoord;
    unsigned short choice;
    unsigned long long index;
    unsigned short playerToMove;
    do
    {
        printBoard();
        printf("Please select 1 to modify cell (0 to submit board)\n");
        scanf(" %hu",&action);
        if(action!=0)
        {
            printf("Please enter 1st coordinate of cell to change\n");
            scanf(" %hu",&xcoord);
            printf("Please enter 2nd coordinate of cell to change\n");
            scanf(" %hu",&ycoord);
            printf("Please enter choice of character\n1\tX\n2\tO\n");
            scanf(" %hu",&choice);
            if(choice>=1 && choice < 3 && xcoord >=0 && xcoord < 3 && ycoord >=0 && ycoord <3)
            {
                board[xcoord][ycoord] = choice;
            }
            else
            {
                printf("Invalid configuration\n");
            }
        }
        else
        {
            unsigned short firstPlayer;
            printf("Please enter who played first\n1\tX\n2\tO\n");
            scanf(" %hu",&firstPlayer);
            int xcount = 0;
            int ycount = 0;
            for(unsigned short i = 0; i<DIMENSION;++i)
            {
                for(unsigned short j = 0; j<DIMENSION;++j)
                {
                    if(board[i][j]==1)
                    {
                        ++xcount;
                    }
                    else if(board[i][j]==2)
                    {
                        ++ycount;
                    }
                }
            }
            if(firstPlayer == 1)
            {
                if(xcount-ycount>1 || xcount-ycount<0)
                {
                    printf("Invalid configuration\n");
                    return 0;
                }
            }
            else if(firstPlayer == 2)
            {
                if(ycount-xcount>1 || ycount-xcount<0) 
                {
                    printf("Invalid configuration\n");
                    return 0;
                }
            }
            printf("Configuration is valid\n");
            for(int i = 0; i<DIMENSION;++i)
            {
                for(int j = 0; j<DIMENSION;++j)
                {
                    vector[3*i+j] = board[i][j];
                }
            }
            printf("\nVector is - ");
            for (int i = 0; i < DIMENSION*DIMENSION; i++)
            {
                printf(" %d",vector[i]);
            }
            
            index = 0;
            for(int i = 0;i<DIMENSION*DIMENSION;++i)
            {
                int numToBeMultiplied = 1;
                for (int j = 0; j < i; j++)
                {
                    numToBeMultiplied *= 3;
                }
                
                index+=vector[(DIMENSION*DIMENSION-1)-i]*numToBeMultiplied;
            }
            printf("\nIndex of this rule is - %llu\n",index);
            if(winningCheck(vector)==1)
            {
                printf("\nThis board is already in winning,thus no next move is possible\n");
                return 0;
            }
            if (xcount-ycount == 0)
            {
                printf("As Xs and Os are equal, the first player has their turn\n");
                playerToMove = firstPlayer;
            }
            else
            {
                printf("As Xs and Os are unequal, the second player has their turn");
                if(firstPlayer == 1)
                {
                    playerToMove = 2;
                }
                else
                {
                    playerToMove = 1;
                }
            }
            unsigned short zeroCounter = 0;
            for (int i = 0; i < DIMENSION*DIMENSION; ++i)
            {
                if(vector[i]==0)
                {
                    ++zeroCounter;
                }
            }
            int** moveMatrix = (int**)calloc(zeroCounter,sizeof(int*));
            for (int i = 0; i < zeroCounter; ++i)
            {
                moveMatrix[i] = (int*)calloc(DIMENSION*DIMENSION,sizeof(int));
            }
            for(int i = 0;i<zeroCounter;++i)
            {
                for(int j = 0;j<DIMENSION*DIMENSION;++j)
                {
                    moveMatrix[i][j] = vector[j];
                }
            }
            int tempZeroIndex = -1;
            int* scoreVector = (int*)calloc(zeroCounter,sizeof(int));
            int* changedIndex = (int*)calloc(zeroCounter,sizeof(int));
            for(int i = 0;i<zeroCounter;++i)
            {
                for(int j = 0;j<DIMENSION*DIMENSION;++j)
                {
                    if(moveMatrix[i][j] == 0 && j>tempZeroIndex)
                    {
                        moveMatrix[i][j] = playerToMove;
                        tempZeroIndex = j;
                        changedIndex[i] = j;
                        break;
                    }
                }
            }
            printf("\nMove matrix is -\n");
            for(int i = 0;i<zeroCounter;++i)
            {

                for(int j = 0; j<DIMENSION*DIMENSION;++j)
                {
                    printf("%d ",moveMatrix[i][j]);
                    if((j+1)%3==0)
                    {
                        printf("\n");
                    }
                }
                printf("\n");
                if(isWinningMove(moveMatrix[i],changedIndex[i],moveMatrix[i][changedIndex[i]]))
                {
                    scoreVector[i] = WINNING_MOVE_SCORE;
                    continue;
                }
                else if(isBlockingMove(moveMatrix[i],changedIndex[i],moveMatrix[i][changedIndex[i]]))
                {
                    scoreVector[i] = BLOCKING_MOVE_SCORE;
                    continue;
                }
                else if(changedIndex[i]==0 || changedIndex[i]==2 ||
                        changedIndex[i]==6 || changedIndex[i]==8
                )
                {
                    scoreVector[i] = CORNER_SCORE;
                    continue;
                }
                else if(changedIndex[i]==1 || changedIndex[i] == 3 || changedIndex[i] == 5 || changedIndex[i]==7)
                {
                    scoreVector[i] = EDGE_SCORE;
                    continue;
                }
                else if(changedIndex[i]==4)
                {
                    scoreVector[i] = CENTER_SCORE;
                    continue;
                }
            }
            int maxScore = 0;
            int maxScoreIndex;
            for(int i = 0;i<zeroCounter;++i)
            {
                for(int j = 0;j<DIMENSION*DIMENSION;++j)
                {
                    printf("%d ",moveMatrix[i][j]);
                }
                if(scoreVector[i]>maxScore)
                {
                    maxScore = scoreVector[i];
                    maxScoreIndex = i;
                }
                printf("- %d\n",scoreVector[i]);
            }
            printf("Hence, the best move is - ");
            for(int i = 0; i<DIMENSION*DIMENSION;++i)
            {
                printf("%d ",moveMatrix[maxScoreIndex][i]);
            }
            printf("with score - %d\n",scoreVector[maxScoreIndex]);
        }
    } while (action != 0);
}