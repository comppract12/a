#include <iostream>
#define N 4
using namespace std;

void printSolution(int board[N][N])
{
    static int solutionCount = 0;
    cout << "solution:" << ++solutionCount << endl;

    for (int i = 0; i < N; i++)
    {
        for (int j = 0; j < N; j++)
        {
            // if 1 then printing Queen
            if (board[i][j] == 1)
            {
                cout << "Q" << (i + 1) << " ";
            }
            // otherwise -
            else
            {
                cout << "-- ";
            }
        }
        cout << endl;
    }
    cout << endl;
}

bool isSafe(int board[N][N], int row, int col)
{
    // checking whether there is any other Queen placed in the same row(Horizonatlly)
    for (int i = 0; i < col; i++)
    {
        if (board[row][i] == 1)
        {
            return false;
        }
    }

    // checking whether there is any other Queen placed in the upper left diagonal
    for (int i = row, j = col; i >= 0 && j >= 0; i--, j--)
    {
        if (board[i][j] == 1)
        {
            return false;
        }
    }

    // checking whether there is any other Queen placed in the Lower left diagonal
    for (int i = row, j = col; i < N && j >= 0; i++, j--)
    {
        if (board[i][j] == 1)
        {
            return false;
        }
    }
    return true;
}

void solveNQueens(int board[N][N], int col, int &solutions)
{
    if (col >= N)
    {
        printSolution(board);
        solutions++;
        return;
    }

    for (int i = 0; i < N; i++)
    {
        // checking whether to place Queen in row->i and column->col is safe or not
        if (isSafe(board, i, col))
        {
            board[i][col] = 1;
            solveNQueens(board, col + 1, solutions);
            board[i][col] = 0; // Backtrack: Remove the queen and try another position
        }
    }
}

void nQueens()
{
    // initializing N*N board grid with all 0
    int board[N][N] = {0};

    // Total number of solutions intializing to 0
    int solutions = 0;

    solveNQueens(board, 0, solutions);

    cout << "Total Solutions for " << N << "*" << N << " board is " << solutions << endl;
}

int main()
{
    nQueens();
    return 0;
}