#include <stdio.h>
#define DIMENSION 3 // To define side of tic-tac-toe board, prevent magic numbers
unsigned short board[DIMENSION][DIMENSION];
unsigned short vector[DIMENSION*DIMENSION];
void initializeBoard(void)
{
    for(unsigned short i = 0; i< DIMENSION;++i)
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

int main(void)
{
    initializeBoard();
    
    unsigned short action;
    unsigned short xcoord;
    unsigned short ycoord;
    unsigned short choice;
    unsigned long long index;
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
        }
    } while (action != 0);
    
}