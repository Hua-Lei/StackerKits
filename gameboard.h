#ifndef GAMEBOARD_H
#define GAMEBOARD_H

#include <QWidget>
#include <QKeyEvent>
#include <QSet>
#include <QTimer>
#include "board.h"
#include "piece.h"
#include "engine.h"
#include <QPainter>

class GameBoard : public QWidget
{
    Q_OBJECT
public:
    explicit GameBoard(QWidget *parent = nullptr);
    void paintEvent(QPaintEvent *) override;
    void keyPressEvent(QKeyEvent *) override;
    void keyReleaseEvent(QKeyEvent *) override;
    void processKeys();
    PieceType* holdPieceTypePtr();
    NextBag* nextsPtr();
private:
    Piece* currentPiece = nullptr;
    QMap<PieceType,QString> colorMap = {{I,"cyan"},{O,"yellow"},{T,"purple"},{S,"green"},{Z,"red"},{L,"orange"},{J,"blue"}};
    QSet<int> pressedKeys={};
    QTimer* frameTimer;
    QElapsedTimer dasTimer;
    QElapsedTimer arrTimer;
    Board* board;
    Engine* engine;
signals:
    void enginePieceTypeChanged();
};

#endif // GAMEBOARD_H
