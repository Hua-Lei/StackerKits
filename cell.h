#ifndef CELL_H
#define CELL_H

#include <QObject>
#include <QColor>
#include <QPointF>
class Cell
{
public:
    explicit Cell(QObject *parent = nullptr);
    Cell(QColor color, QPoint rpos);
    void setpos(double x, double y);
    QPointF getpos() const;
    QPoint getrpos() const {return rpos;}
    QColor getcolor() const {return color;}
    bool isEmpty() const {return isempty;}
    void copyCellState(const Cell& cell);
    void fill(QColor newcolor) {isempty = false;color=newcolor;}
    void clear() {isempty = true;color="grey";}
protected:
    bool isempty;
    QColor color;
    QPointF pos;
    QPoint rpos; // only used for pieces
signals:
};

#endif // CELL_H
