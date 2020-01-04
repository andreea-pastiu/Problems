/*
3.13. A labyrinth is coded using a m x n matrix. The passages are represented by elements equal to 1
placed on successive positions on a row or on a column. The requirement is to display all the traces
that lead to the exit of the labyrinth, starting from an initial position ( i, j ). It is forbidden to pass
more than once through the same point.
*/
#include <stdio.h>
#include <stdlib.h>

typedef struct dir
{
    int line, column;
}direction;
direction dir[8]={{-1, 0}, {0, 1}, {1, 0}, {0, -1}};
typedef struct el
{
    int line, column, directionNo;
}cell;
void readData(int ***labyrinth, int *n, int *m, int *lineStart, int *columnStart, int *lineEnd, int *columnEnd, int *ptr)
{
    fscanf(ptr, "%d%d%d%d%d%d", n, m, lineStart, columnStart, lineEnd, columnEnd);
    (*labyrinth) = (int**) malloc((*n) * sizeof(int*));
    for (int i = 0; i < (*n); i++)
    {
        (*labyrinth)[i] = (int *) malloc((*m) * sizeof(int));
        for (int j = 0; j < (*m); j++)
            fscanf(ptr, "%d", &(*labyrinth)[i][j]);
    }
}
void printSolution(cell *solution, int solLength, int *solExists)
{
    int i;
    (*solExists) = 1;
    for (i = 0; i <= solLength + 1; i++)
        printf("(%d;%d)", solution[i].line, solution[i].column);
    printf("\n");
}
int canGo (cell *solution, int solLength, int** labyrinth, int n, int m, int lineNext, int columnNext)
{
    int v=1, i;
    for (i = 0; i <= solLength; i++)
        if (lineNext == solution[i].line && columnNext == solution[i].column)
            v = 0;
    if (columnNext < 0 || columnNext > m - 1 || lineNext < 0 || lineNext > n - 1)
        v = 0;
    else
        if (labyrinth[lineNext][columnNext] == 0)
            v = 0;
    return v;
}
void solve(int **labyrinth, int n, int m, int lineStart, int columnStart, int lineEnd, int columnEnd, int solLength, cell *solution, int *solExists)
{
    int lineNext, columnNext;
    solution[solLength].line = lineStart;
    solution[solLength].column = columnStart;
    solution[solLength].directionNo = -1;
    while (solution[solLength].directionNo < 3)
    {
        solution[solLength].directionNo++;
        lineNext = solution[solLength].line + dir[solution[solLength].directionNo].line;
        columnNext = solution[solLength].column + dir[solution[solLength].directionNo].column;
        if (canGo(solution, solLength, labyrinth, n, m, lineNext, columnNext))
            if (lineNext == lineEnd && columnNext == columnEnd)
            {
                solution[solLength + 1].line = lineNext;
                solution[solLength + 1].column = columnNext;
                printSolution(solution, solLength, solExists);
            }
            else
            {
                solve(labyrinth, n, m, lineNext, columnNext, lineEnd, columnEnd, solLength + 1, solution, solExists);
            }
    }
}

int main()
{
    FILE *ptr = fopen("..\\in.txt", "r");
    if (ptr == NULL)
    {
        printf("No input file");
        exit(0);
    }
    int **labyrinth, n, m, lineStart, columnStart, lineEnd, columnEnd, solExists = 0;
    readData(&labyrinth, &n, &m, &lineStart, &columnStart, &lineEnd, &columnEnd, ptr);
    cell *solution;
    solution = (cell *) malloc(n * m * sizeof(cell));
    solve(labyrinth, n, m, lineStart, columnStart, lineEnd, columnEnd, 0, solution, &solExists);
    if (!solExists)
        printf("No solution");
    for(int i = 0; i < n; i++)
        free(labyrinth[i]);
    free(labyrinth);
    free(solution);

    fclose(ptr);

    return 0;
}