#ifndef NEXTBAG_H
#define NEXTBAG_H

#include <QObject>
#include <QQueue>
#include "piece.h"
#include <QRandomGenerator>
class NextBag : QObject
{
    Q_OBJECT
public:
    NextBag();
    void AddBag();
    PieceType dequeue();

private:
    QQueue<PieceType> currentBag = {};
    QVector<PieceType> RandomBag = {I,O,S,Z,T,L,J};
};

#endif // NEXTBAG_H
