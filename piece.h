#ifndef PIECE_H
#define PIECE_H
#include <QVector>
#include <QObject>
#include <QPair>
#include <QMap>
#include "cell.h"
enum PieceType {I,O,S,Z,T,L,J};
enum RotationType {Init,R90,M180,L90};
class Engine;
class Piece
{
public:
    friend Engine;
    Piece(PieceType type, QPoint initPos);
    Piece(const Piece& piece);
    // virtual void rotateLeft() = 0;
    // virtual void rotateRight() = 0;
    // virtual void moveLeft() = 0;
    // virtual void moveRight() = 0;
    PieceType pieceType(){return type;}
    QPair<QVector<QPoint>,QPoint> getPieceLoc();
    void setPos(QPoint newpos) {pos = newpos;}
    void updatePoints(QVector<QPoint> newpoints);
    RotationType counterRotType(RotationType currentType);
    RotationType nextRotType(RotationType currentType);
private:
    PieceType type;
    RotationType rotation;
    QVector<Cell> cells;
    QPoint pos;
    QMap<PieceType,QString> colorMap = {{I,"cyan"},{O,"yellow"},{T,"purple"},{S,"green"},{Z,"red"},{L,"orange"},{J,"blue"}};
};

#endif // PIECE_H
