#include "board.h"
#include <array>
Board::Board(QWidget *parent)
    : QWidget{parent}
{
    for(int a = 0;a<20;a++) {
        for(int b = 0;b<10;b++){
            board[a][b].setpos(b,a); //行列和xy相反
        }
    }
}

Cell& Board::getCell(int row, int col)
{
    if(row>=20 || row <0 || col >=10 || col <0) assert(0);
    return board[row][col];
}

void Board::clear() {
    for(int a = 0;a<20;a++) {
        for(int b = 0;b<10;b++){
            board[a][b].clear(); //行列和xy相反
        }
    }
}

