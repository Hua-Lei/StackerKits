#ifndef ENGINE_H
#define ENGINE_H

#include <QObject>
#include "piece.h"
#include <QKeyEvent>
#include <algorithm>
#include <QWidget>
#include "board.h"
#include "nextbag.h"
class Engine : public QObject
{
    Q_OBJECT
public:
    explicit Engine(Piece* currentPiece, Board* board, QObject *parent = nullptr);
    bool isCollision(QVector<QPoint>& cells, QPoint pos);
    bool moveLeft();
    bool moveRight();
    bool hardDrop();
    bool moveDown();
    void lock();
    void rotateLeft();
    void rotateRight();
    bool isFilledLine(int line);
    QPair<QPoint,QColor> getShadowPos(Piece* piece);
    void examineAndClearLines(QSet<int> lines);
    int rotTypeDirectedDistance(RotationType init, RotationType target);
    QPair<QVector<QPoint>,QPoint> rotateAttemptRes(RotationType init, RotationType target);
private:
    NextBag nexts;
    Piece* currentPiece;
    Board* board;
    QMap<QPair<RotationType,RotationType>,QVector<QPoint>> offsetTableMain = {{{Init,R90},{QPoint(0,0),QPoint(-1,0),QPoint(-1,-1),QPoint(0,2),QPoint(-1,2)}},
                                                                                 {{R90,Init},{QPoint(0,0),QPoint(1,0),QPoint(1,1),QPoint(0,-2),QPoint(1,-2)}},
                                                                                 {{R90,M180},{QPoint(0,0),QPoint(1,0),QPoint(1,1),QPoint(0,-2),QPoint(1,-2)}},
                                                                                {{M180,R90},{QPoint(0,0),QPoint(-1,0),QPoint(-1,-1),QPoint(0,2),QPoint(-1,2)}},
                                                                                {{M180,L90},{QPoint(0,0),QPoint(1,0),QPoint(1,-1),QPoint(0,2),QPoint(1,2)}},
                                                                                {{L90,M180},{QPoint(0,0),QPoint(-1,0),QPoint(-1,1),QPoint(0,-2),QPoint(-1,-2)}},
                                                                                {{L90,Init},{QPoint(0,0),QPoint(-1,0),QPoint(-1,1),QPoint(0,-2),QPoint(-1,-2)}},
                                                                                {{Init,L90},{QPoint(0,0),QPoint(1,0),QPoint(1,-1),QPoint(0,2),QPoint(1,2)}}
                                                }; //besides I,O
    //Seq: Init->R90->M180->L90
    QMap<QPair<RotationType,RotationType>,QVector<QPoint>> offsetTableI = {{{Init,R90},{QPoint(0,0),QPoint(-2,0),QPoint(1,0),QPoint(-2,1),QPoint(1,-2)}},
                                                                            {{R90,Init},{QPoint(0,0),QPoint(2,0),QPoint(-1,0),QPoint(2,-1),QPoint(-1,2)}},
                                                                            {{R90,M180},{QPoint(0,0),QPoint(-1,0),QPoint(2,0),QPoint(-1,-2),QPoint(2,1)}},
                                                                            {{M180,R90},{QPoint(0,0),QPoint(1,0),QPoint(-2,0),QPoint(1,2),QPoint(-2,-1)}},
                                                                            {{M180,L90},{QPoint(0,0),QPoint(2,0),QPoint(-1,0),QPoint(2,-1),QPoint(-1,2)}},
                                                                            {{L90,M180},{QPoint(0,0),QPoint(-2,0),QPoint(1,0),QPoint(-2,1),QPoint(1,-2)}},
                                                                            {{L90,Init},{QPoint(0,0),QPoint(1,0),QPoint(-2,0),QPoint(1,2),QPoint(-2,-1)}},
                                                                            {{Init,L90},{QPoint(0,0),QPoint(-1,0),QPoint(2,0),QPoint(-1,-2),QPoint(2,1)}}
                                                                        };
signals:
    void updateRequired();
};

#endif // ENGINE_H
