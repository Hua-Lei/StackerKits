#ifndef BOARD_H
#define BOARD_H

#include <QWidget>
#include "cell.h"
class Board : public QWidget
{
    Q_OBJECT
public:
    explicit Board(QWidget *parent = nullptr);
    Cell& getCell(int row,int col);
private:
    std::array<std::array<Cell,10>,20> board;
signals:
};

#endif // BOARD_H
