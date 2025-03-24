#include "piece.h"
#include <QDebug>

Piece::Piece(PieceType type, QPoint initPos)
    :pos{initPos},type{type},rotation{Init}
{
    switch (type) {
    case PieceType::I:
        cells = {Cell(colorMap[I], QPoint(0,0)),
                 Cell(colorMap[I], QPoint(-1,0)),
                 Cell(colorMap[I], QPoint(1,0)),
                 Cell(colorMap[I], QPoint(2,0))};
        break;
    case PieceType::O:
        cells = {Cell(colorMap[O], QPoint(0,0)),
                 Cell(colorMap[O], QPoint(1,0)),
                Cell(colorMap[O], QPoint(0,1)),
                Cell(colorMap[O], QPoint(1,1))};
        break;
    case PieceType::T:
        cells = {Cell(colorMap[T], QPoint(0,0)),
                 Cell(colorMap[T], QPoint(-1,0)),
                 Cell(colorMap[T], QPoint(1,0)),
                 Cell(colorMap[T], QPoint(0,-1))};
        break;
    case PieceType::S:
        cells = {Cell(colorMap[S], QPoint(0,0)),
                 Cell(colorMap[S], QPoint(-1,0)),
                 Cell(colorMap[S], QPoint(0,-1)),
                 Cell(colorMap[S], QPoint(1,-1))};
        break;
    case PieceType::Z:
        cells = {Cell(colorMap[Z], QPoint(0,0)),
                 Cell(colorMap[Z], QPoint(1,0)),
                 Cell(colorMap[Z], QPoint(0,-1)),
                 Cell(colorMap[Z], QPoint(-1,-1))};
        break;
    case PieceType::L:
        cells = {Cell(colorMap[L], QPoint(0,0)),
                 Cell(colorMap[L], QPoint(-1,0)),
                 Cell(colorMap[L], QPoint(1,0)),
                 Cell(colorMap[L], QPoint(1,-1))};
        break;
    case PieceType::J:
        cells = {Cell(colorMap[J], QPoint(0,0)),
                 Cell(colorMap[J], QPoint(-1,0)),
                 Cell(colorMap[J], QPoint(1,0)),
                 Cell(colorMap[J], QPoint(-1,-1))};
        break;
    default:
        break;
    }
}

QPair<QVector<QPoint>,QPoint> Piece::getPieceLoc() {
    QVector<QPoint> points = {};
    for(auto i : cells) {
        points.push_back(i.getrpos());
    }
    return {points,pos};
}

void Piece::updatePoints(QVector<QPoint> newpoints) {
    QVector<Cell> newcells={};
    for(auto &point : newpoints) {
        newcells.push_back({colorMap[type],point});
    }
    cells=newcells;
}

RotationType Piece::counterRotType(RotationType currentType) {
    if(currentType == 0) return RotationType(3);
    return RotationType(currentType-1);
}
RotationType Piece::nextRotType(RotationType currentType) {
    qDebug() << rotation << RotationType((currentType+1) % 4);
    return RotationType((currentType+1) % 4);
}


// Piece::Piece(const Piece& piece) {
//     type = piece.type;
//     pos = piece.pos;

// }
