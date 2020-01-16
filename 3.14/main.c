/*
A knight is placed in the upper left square on a chess board of size n x n. Display all the possible
paths of the knight on the chess board, such a way that every square is reached only once.
*/
#include <stdio.h>
#include <stdlib.h>

typedef struct dir
{
    int line, column;
}direction;
direction dir[8]={{-2, 1}, {-1, 2}, {1, 2}, {2, 1}, {2, -1}, {1, -2}, {-1, -2}, {-2, -1}};
typedef struct el
{
    int line, column, directionNo;
}cell;

void printSolution(cell *solution, int solLength, int *solExists)
{
    int i;
    (*solExists) = 1;
    for (i = 0; i <= solLength + 1; i++)
        printf("(%d;%d)", solution[i].line, solution[i].column);
    printf("\n");
}
int canGo (cell *solution, int solLength, int** board, int n, int lineNext, int columnNext)
{
    int v=1, i;
    for (i = 0; i <= solLength; i++)
        if (lineNext == solution[i].line && columnNext == solution[i].column)
            v = 0;
    if (columnNext < 0 || columnNext > n - 1 || lineNext < 0 || lineNext > n - 1)
        v = 0;
    return v;
}
void solve(int **board, int n, int lineStart, int columnStart, int solLength, cell *solution, int *solExists)
{
    int lineNext, columnNext;
    solution[solLength].line = lineStart;
    solution[solLength].column = columnStart;
    solution[solLength].directionNo = -1;
    while (solution[solLength].directionNo < 7)
    {
        solution[solLength].directionNo++;
        lineNext = solution[solLength].line + dir[solution[solLength].directionNo].line;
        columnNext = solution[solLength].column + dir[solution[solLength].directionNo].column;
        if (canGo(solution, solLength, board, n, lineNext, columnNext))
            if (solLength == n*n-2)
            {
                solution[solLength + 1].line = lineNext;
                solution[solLength + 1].column = columnNext;
                printSolution(solution, solLength, solExists);
            }
            else
            {
                solve(board, n, lineNext, columnNext, solLength + 1, solution, solExists);
            }
    }
}

int main()
{
    int **board, n, lineStart=0, columnStart=0, solExists = 0;
    printf("Give n: ");
    scanf("%d", &n);
    cell *solution;
    solution = (cell *) malloc(n * n * sizeof(cell));
    solve(board, n, lineStart, columnStart, 0, solution, &solExists);
    if (!solExists)
        printf("No solution");
    for(int i = 0; i < n; i++)
        free(board[i]);
    free(board);
    free(solution);

    return 0;
}