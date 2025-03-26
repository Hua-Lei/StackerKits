#include "gameboard.h"


const int DAS = 110;
const int ARR = 10;
GameBoard::GameBoard(QWidget *parent)
    : QWidget{parent}
{
    setFocusPolicy(Qt::ClickFocus);
    frameTimer = new QTimer();
    connect(frameTimer,&QTimer::timeout,this,&GameBoard::processKeys);
    frameTimer->start(5);
    board = new Board();
    currentPiece = new Piece(PieceType::I, QPoint(4,1));
    engine = new Engine(currentPiece,board);
    setAttribute(Qt::WA_KeyCompression, false); //TODO
    connect(engine,&Engine::updateRequired,this,QOverload<>::of(&QWidget::update));
    connect(engine,&Engine::pieceTypeChanged,this,&GameBoard::enginePieceTypeChanged);

}
void GameBoard::keyPressEvent(QKeyEvent * event) {
    switch(event->key()) {
    case Qt::Key_Left:
        pressedKeys.insert(event->key());
        break;
    case Qt::Key_Right:
        pressedKeys.insert(event->key());
        break;
    case Qt::Key_Space:
        engine->hardDrop();
        break;
    case Qt::Key_Down:
        pressedKeys.insert(event->key());
        break;
    case Qt::Key_Z:
        engine->rotateLeft();
        break;
    case Qt::Key_X:
        engine->rotateRight();
        break;
    case Qt::Key_Shift:
        engine->hold();
        break;
    default:
        QWidget::keyPressEvent(event);
        break;
    }
}

void GameBoard::keyReleaseEvent(QKeyEvent * event) {
    pressedKeys.remove(event->key());
    switch(event->key()) {
    case Qt::Key_Left:
        dasTimer.invalidate();
        arrTimer.invalidate();
        break;
    case Qt::Key_Right:
        dasTimer.invalidate();
        arrTimer.invalidate();
        break;
    }

}

void GameBoard::processKeys() {
    if(pressedKeys.contains(Qt::Key_Left)) {
        if(arrTimer.isValid()) {
            if(arrTimer.elapsed()>=ARR) {
                engine->moveLeft();
                arrTimer.restart();
            }
        }
        else if(!dasTimer.isValid()) {
            engine->moveLeft();
            dasTimer.start();
        } else if(dasTimer.elapsed()>=DAS) {
            engine->moveLeft();
            arrTimer.start();
        }

    }
    if(pressedKeys.contains(Qt::Key_Right)) {
        if(arrTimer.isValid()) {
            if(arrTimer.elapsed()>=ARR) {
                engine->moveRight();
                arrTimer.restart();
            }
        }
        else if(!dasTimer.isValid()) {
            engine->moveRight();
            dasTimer.start();
        } else if(dasTimer.elapsed()>=DAS) {
            engine->moveRight();
            arrTimer.start();
        }
    }
    if(pressedKeys.contains(Qt::Key_Down)) {
        engine->moveDown();
    }
}

void GameBoard::paintEvent(QPaintEvent *){
    double cellLen = this->geometry().width()/10.0;
    QSizeF sizef(cellLen,cellLen);

    QPainter painter(this);
    for(int a = 0;a<20;a++) {
        for(int b = 0;b<10;b++){
            QPointF pos = board->getCell(a,b).getpos();
            pos.rx()*=cellLen;pos.ry()*=cellLen;
            QRectF rectf(pos,sizef);
            QColor color = board->getCell(a,b).getcolor();
            painter.fillRect(rectf,color);
            painter.setPen(QPen(Qt::gray, 1, Qt::DotLine));
            painter.setBrush(Qt::NoBrush);
            painter.drawRect(rectf);
        }
    }
    if(currentPiece != nullptr) {
        auto [points,piecepos] = currentPiece->getPieceLoc();
        for(auto &point : points) {
            QPointF pos = point + piecepos;
            pos.rx()*=cellLen;pos.ry()*=cellLen;
            QRectF rectf(pos,sizef);
            QColor color = colorMap[currentPiece->pieceType()];
            painter.fillRect(rectf,color);
        }
        auto [shadowpos, color] = engine->getShadowPos(currentPiece);
        for(auto &point : points) {
            QPointF pos = point + shadowpos;
            pos.rx()*=cellLen;pos.ry()*=cellLen;
            QRectF rectf(pos,sizef);
            QColor color = colorMap[currentPiece->pieceType()];
            color.setAlpha(100);
            painter.fillRect(rectf,color);
        }
    }
}
PieceType* GameBoard::holdPieceTypePtr() {
    return &engine->holdPieceType;
}
NextBag* GameBoard::nextsPtr() {
    return &engine->nexts;
}
