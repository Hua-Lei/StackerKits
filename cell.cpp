#include "cell.h"

Cell::Cell(QObject *parent)
{
    isempty = true;
    color = "grey";
}

Cell::Cell(QColor color, QPoint rpos)
    : color{color},rpos{rpos}
{
    isempty = false;
}

void Cell::setpos(double x, double y)
{
    pos = {x,y};
}

QPointF Cell::getpos() const
{
    return pos;
}

void Cell::copyCellState(const Cell& cell) {
    isempty = cell.isEmpty();
    color = cell.color;
}
