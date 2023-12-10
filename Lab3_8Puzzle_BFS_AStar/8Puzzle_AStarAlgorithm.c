#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define COST 1
#define DIMENSION 3

int goalState[DIMENSION][DIMENSION] = {{1, 2, 3}, {8, 0, 4}, {7, 6, 5}};

typedef struct NODE
{
    int boardPosition[DIMENSION][DIMENSION];
    struct NODE *parent;
    int gCurrent;
    struct NODE *child;
    int heuristic_value;
    struct NODE *next;
} Node;

void printBoard(int board[DIMENSION][DIMENSION])
{
    for (int i = 0; i < DIMENSION; ++i)
    {
        printf("-------------\n");
        for (int j = 0; j < DIMENSION; ++j)
        {
            printf("|");
            if (board[i][j] == 0)
            {
                printf_s("   ");
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

void getBoardPosition(int board[DIMENSION][DIMENSION])
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

int heuristic_misplaced_tiles(int board[DIMENSION][DIMENSION], int goalPosition[DIMENSION][DIMENSION])
{
    int misplaced_tiles = 0;
    for (int i = 0; i < DIMENSION; ++i)
    {
        for (int j = 0; j < DIMENSION; ++j)
        {
            if (board[i][j] != goalPosition[i][j])
            {
                ++misplaced_tiles;
            }
        }
    }
    return misplaced_tiles / 2;
}

Node *createNode(int board[DIMENSION][DIMENSION], Node *parent, Node *child, Node *next, int gCurrent)
{
    Node *newNode = (Node *)malloc(sizeof(Node));
    for (int i = 0; i < DIMENSION; ++i)
    {
        for (int j = 0; j < DIMENSION; ++j)
        {
            newNode->boardPosition[i][j] = board[i][j];
        }
    }
    newNode->parent = parent;
    newNode->heuristic_value = heuristic_misplaced_tiles(board, goalState);
    if (parent == NULL)
    {
        newNode->gCurrent = 0;
    }
    else
    {
        newNode->gCurrent = parent->gCurrent + gCurrent;
    }
    newNode->child = child;
    newNode->next = next;
    return newNode;
}

void insertPriority(Node **listNode, Node *node)
{
    if (*listNode == NULL)
    {
        *listNode = node;
        return;
    }
    Node *tempNode = (*listNode);
    if ((*listNode)->heuristic_value + (*listNode)->gCurrent > node->heuristic_value + node->gCurrent)
    {
        node->next = (*listNode);
        (*listNode) = node;
        return;
    }
    while ((tempNode)->next != NULL && (tempNode)->heuristic_value + (tempNode)->gCurrent <= node->heuristic_value + node->gCurrent)
    {
        tempNode = (tempNode)->next;
    }
    node->next = tempNode->next;
    tempNode->next = node;
    return;
}

Node *removePriority(Node **listHead)
{
    Node *temp = *listHead;
    *listHead = (*listHead)->next;
    return temp;
}

void findGap(Node *tempNode, int *gapX, int *gapY)
{
    for (int i = 0; i < DIMENSION; ++i)
    {
        for (int j = 0; j < DIMENSION; ++j)
        {
            if (tempNode->boardPosition[i][j] == 0)
            {
                *gapX = i;
                *gapY = j;
                return;
            }
        }
    }
}

void printList(Node *head)
{
    int index = 0;
    if (head == NULL)
    {
        printf("Given linked list is empty\n");
        return;
    }
    while (head != NULL)
    {
        printf("------------------------------------\n");
        printf("Board position - %d\n",index);
        printBoard(head->boardPosition);
        printf("Node parent - %p\n", head->parent);
        printf("Node self - %p\n", head);
        printf("Node child - %p\n", head->child);
        printf("Node next - %p\n", head->next);
        printf("Node g - %d\n", head->gCurrent);
        printf("Node heuristic value - %d\n", head->heuristic_value);
        ++index;
        head = head->next;
    }
    printf("------------------------------------\n");
}

bool compareBoardPositions(int board1[DIMENSION][DIMENSION], int board2[DIMENSION][DIMENSION])
{
    for (int i = 0; i < DIMENSION; ++i)
    {
        for (int j = 0; j < DIMENSION; ++j)
        {
            if (board1[i][j] != board2[i][j])
            {
                return false;
            }
        }
    }
    return true;
}

bool removeSpecific(Node **listHead, Node *node)
{
    if (*listHead == NULL)
    {
        return false;
    }
    if (compareBoardPositions((*listHead)->boardPosition, node->boardPosition) && (*listHead)->gCurrent + (*listHead)->heuristic_value > node->gCurrent + node->heuristic_value)
    {
        Node *tempPtr = *listHead;
        *listHead = (*listHead)->next;
        free(tempPtr);
        printf("Node found at start, removing\n");
        return true;
    }
    Node *prevNode = NULL;
    Node *travNode = *listHead;
    while ((compareBoardPositions((*listHead)->boardPosition, node->boardPosition) != true) && travNode != NULL)
    {
        prevNode = travNode;
        travNode = travNode->next;
    }
    if (travNode == NULL)
    {
        printf("Board position not found\n");
        return false;
    }
    if (travNode->gCurrent + travNode->heuristic_value > node->gCurrent + node->heuristic_value)
    {
        prevNode->next = prevNode->next->next;
        free(travNode);
        printf("Found node in middle of list, removing\n");
        return true;
    }
    printf("Earlier cost & heuristic is better\n");
    return false;
}

void printSolution(Node* solvedNode)
{
    Node* tempNode = solvedNode;
    int i = 0;
    while(tempNode!=NULL)
    {
        printf("Board position - %d\n",i);
        printBoard(tempNode->boardPosition);
        ++i;
        tempNode = tempNode->parent;
    }
}

int main(void)
{
    int originalBoard[DIMENSION][DIMENSION];
    for(int i = 0; i < DIMENSION; ++i)
    {
        for(int j = 0; j < DIMENSION; ++j)
        {
            originalBoard[i][j] = 0;
        }
    }
    printBoard(originalBoard);
    getBoardPosition(originalBoard);
    printf("This is the final board position - \n");
    printBoard(originalBoard);
    Node *OPENnode = NULL;
    Node *veryTempNode = createNode(originalBoard, NULL, NULL, NULL, 0);
    veryTempNode->gCurrent = 0;
    insertPriority(&OPENnode, veryTempNode);
    Node *CLOSEDnode = NULL;
    int bruh = 0;
    while (OPENnode != NULL)
    {
        int gapX, gapY;
        Node *tempNode = removePriority(&OPENnode);
        printf("\n\nNew move being started\n\n");
        printf("Initial board considered - \n");
        printBoard(tempNode->boardPosition);
        if(tempNode->heuristic_value == 0)
        {
            printf("Solution found\n");
            printSolution(tempNode);
            return 0;
        }
        findGap(tempNode, &gapX, &gapY);
        if (gapX + 1 < DIMENSION)
        {
            int tempNewBoard[DIMENSION][DIMENSION];
            for (int i = 0; i < DIMENSION; ++i)
            {
                for (int j = 0; j < DIMENSION; ++j)
                {
                    tempNewBoard[i][j] = tempNode->boardPosition[i][j];
                }
            }
            int temp = tempNewBoard[gapX][gapY];
            tempNewBoard[gapX][gapY] = tempNewBoard[gapX + 1][gapY];
            tempNewBoard[gapX + 1][gapY] = temp;
            veryTempNode = createNode(tempNewBoard, tempNode, NULL, NULL, COST);
            if(veryTempNode->heuristic_value == 0)
            {
                printf("Solution found\n");
                printSolution(veryTempNode);
                return 0;
            }
            if (removeSpecific(&OPENnode, veryTempNode))
            {
                insertPriority(&OPENnode, veryTempNode);
                continue;
            }
            if (removeSpecific(&CLOSEDnode, veryTempNode))
            {
                insertPriority(&CLOSEDnode, veryTempNode);
                continue;
            }
            insertPriority(&OPENnode, veryTempNode);
        }
        if (gapX - 1 > -1)
        {
            int tempNewBoard[DIMENSION][DIMENSION];
            for (int i = 0; i < DIMENSION; ++i)
            {
                for (int j = 0; j < DIMENSION; ++j)
                {
                    tempNewBoard[i][j] = tempNode->boardPosition[i][j];
                }
            }
            int temp = tempNewBoard[gapX][gapY];
            tempNewBoard[gapX][gapY] = tempNewBoard[gapX - 1][gapY];
            tempNewBoard[gapX - 1][gapY] = temp;
            veryTempNode = createNode(tempNewBoard, tempNode, NULL, NULL, COST);
            if(veryTempNode->heuristic_value == 0)
            {
                printf("Solution found\n");
                printSolution(veryTempNode);
                return 0;
            }
            if (removeSpecific(&OPENnode, veryTempNode))
            {
                insertPriority(&OPENnode, veryTempNode);
                continue;
            }
            if (removeSpecific(&CLOSEDnode, veryTempNode))
            {
                insertPriority(&CLOSEDnode, veryTempNode);
                continue;
            }
            insertPriority(&OPENnode, veryTempNode);
        }
        if (gapY + 1 < DIMENSION)
        {
            int tempNewBoard[DIMENSION][DIMENSION];
            for (int i = 0; i < DIMENSION; ++i)
            {
                for (int j = 0; j < DIMENSION; ++j)
                {
                    tempNewBoard[i][j] = tempNode->boardPosition[i][j];
                }
            }
            int temp = tempNewBoard[gapX][gapY];
            tempNewBoard[gapX][gapY] = tempNewBoard[gapX][gapY + 1];
            tempNewBoard[gapX][gapY + 1] = temp;
            veryTempNode = createNode(tempNewBoard, tempNode, NULL, NULL, COST);
            if(veryTempNode->heuristic_value == 0)
            {
                printf("Solution found\n");
                printSolution(veryTempNode);
                return 0;
            }
            if (removeSpecific(&OPENnode, veryTempNode))
            {
                insertPriority(&OPENnode, veryTempNode);
                continue;
            }
            if (removeSpecific(&CLOSEDnode, veryTempNode))
            {
                insertPriority(&CLOSEDnode, veryTempNode);
                continue;
            }
            insertPriority(&OPENnode, veryTempNode);
        }
        if (gapY - 1 > -1)
        {
            int tempNewBoard[DIMENSION][DIMENSION];
            for (int i = 0; i < DIMENSION; ++i)
            {
                for (int j = 0; j < DIMENSION; ++j)
                {
                    tempNewBoard[i][j] = tempNode->boardPosition[i][j];
                }
            }
            int temp = tempNewBoard[gapX][gapY];
            tempNewBoard[gapX][gapY] = tempNewBoard[gapX][gapY - 1];
            tempNewBoard[gapX][gapY - 1] = temp;
            veryTempNode = createNode(tempNewBoard, tempNode, NULL, NULL, COST);
            if(veryTempNode->heuristic_value == 0)
            {
                printf("Solution found\n");
                printSolution(veryTempNode);
                return 0;
            }
            if (removeSpecific(&OPENnode, veryTempNode))
            {
                insertPriority(&OPENnode, veryTempNode);
                continue;
            }
            if (removeSpecific(&CLOSEDnode, veryTempNode))
            {
                insertPriority(&CLOSEDnode, veryTempNode);
                continue;
            }
            insertPriority(&OPENnode, veryTempNode);
        }
        insertPriority(&CLOSEDnode, tempNode);
        printf("OPEN LIST BEGIN\n");
        printList(OPENnode);
        printf("OPEN LIST END\n");
        printf("\n\n\n");
        printf("CLOSED LIST BEGIN\n");
        printList(CLOSEDnode);
        printf("CLOSED LIST END\n");
        ++bruh;
    }
}