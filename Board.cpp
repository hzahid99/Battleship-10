#include "Board.h"
#include <string>
#include <iostream>
using namespace std;
/*
 *  intializes the 2d array and creates the 10 x 10 board with all *'s
*/
Board::Board()
{
    Boardarr = new string *[10];
    for (int i = 0; i < 10; i++)
    {
        Boardarr[i] = new string[10];
    }
    for (int i = 0; i < 10; i++)
    {
        for (int j = 0; j < 10; j++)
        {
            Boardarr[i][j] = "*";
        }
    }
}
/*
 *  deletes the 2d array
*/
Board::~Board()
{

    for(int i = 0; i < 10; i++)
    {
        delete[] Boardarr[i];
    }

    delete[] Boardarr;
}

string** Board::getArr()
{
    return Boardarr;
}

string Board::at(int row, int col)
{
    return Boardarr[row][col];
}

void Board::setBoard(string mark, int row, int col)
{
    Boardarr[row][col] = mark;
}
