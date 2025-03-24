#include "engine.h"
#include <qwidget.h>

Engine::Engine(Piece* currentPiece, Board* board, QObject *parent)
    : QObject{parent},currentPiece{currentPiece},board{board}
{
    *currentPiece=Piece(nexts.dequeue(),QPoint(1,4));
}

bool Engine::isCollision(QVector<QPoint>& points, QPoint pos) {
    for(auto &point : points) {
        QPoint absPos = point + pos;
        int x = absPos.x();
        int y = absPos.y();
        if(x < 0 || x >= 10 || y<0 || y>=20) {return true;}
        if(!board->getCell(y,x).isEmpty()) {return true;}
    }
    return false;
}

bool Engine::moveLeft() {
    auto [points,pos] = currentPiece->getPieceLoc();
    int x = pos.x();
    int y = pos.y();
    if(isCollision(points, QPoint(x-1,y))) {
        return false;
    }
    else {
        currentPiece->setPos(QPoint(x-1,y));
        emit updateRequired();
        return true;
    }
}
bool Engine::moveRight() {
    auto [points,pos] = currentPiece->getPieceLoc();
    int x = pos.x();
    int y = pos.y();
    if(isCollision(points, QPoint(x+1,y))) {
        return false;
    }
    else {
        currentPiece->setPos(QPoint(x+1,y));
        emit updateRequired();
        return true;
    }
}
bool Engine::moveDown() {
    auto [points,pos] = currentPiece->getPieceLoc();
    int x = pos.x();
    int y = pos.y();
    if(isCollision(points, QPoint(x,y+1))) {
        return false;
    }
    else {
        currentPiece->setPos(QPoint(x,y+1));
        emit updateRequired();
        return true;
    }
}
bool Engine::hardDrop() {
    while(moveDown());
    lock();
    return true;
}

void Engine::rotateLeft() {
    if(currentPiece->type == PieceType::O) {return;}
    if(currentPiece->type == PieceType::I) {
        QPoint postRotPosI = currentPiece->pos;
        switch (currentPiece->rotation) {
        case Init:
            postRotPosI+=QPoint(0,1);
            break;
        case R90:
            postRotPosI+=QPoint(-1,0);
            break;
        case M180:
            postRotPosI+=QPoint(0,-1);
            break;
        case L90:
            postRotPosI+=QPoint(1,0);
            break;
        default:
            break;
        }

        auto init = currentPiece->rotation;auto target = currentPiece->counterRotType(currentPiece->rotation);

//TODO: optimize code here(rotleft and rotright)
        QVector<QPoint> tempPiecePoints = {};
        if(target == currentPiece->nextRotType(init)) {
            for(auto a : currentPiece->cells) {
                auto [rx,ry] = a.getrpos();
                tempPiecePoints.push_back(QPoint(-ry,rx));
            }
        } else {
            for(auto a : currentPiece->cells) {
                auto [rx,ry] = a.getrpos();
                tempPiecePoints.push_back(QPoint(ry,-rx));
            }
        }
        auto cpos = postRotPosI; //different from ZSLJT,rotation center is the geometry center

        QPair<RotationType,RotationType> request = {init,target};
        QVector<QPoint> requestTable = offsetTableI[request];
        for(auto &i : requestTable) {
            // i is the current offset
            if(!isCollision(tempPiecePoints,cpos+i)) {
                currentPiece->updatePoints(tempPiecePoints);
                currentPiece->pos = cpos+i;
                qDebug() << cpos << cpos+i << currentPiece->rotation;
                currentPiece->rotation = currentPiece->counterRotType(currentPiece->rotation);
                break;

            }
        }

    } else {
        auto [res,offset] = rotateAttemptRes(currentPiece->rotation,currentPiece->counterRotType(currentPiece->rotation));
        if(!res.isEmpty()) { // if success,then update points,pos,rotationType
            currentPiece->updatePoints(res);
            currentPiece->pos += offset;
            currentPiece->rotation = currentPiece->counterRotType(currentPiece->rotation);

        }
    }
    emit updateRequired();

}

void Engine::rotateRight() {
    if(currentPiece->type == PieceType::O) {return;}
    if(currentPiece->type == PieceType::I) {
        QPoint postRotPosI = currentPiece->pos;
        switch (currentPiece->rotation) {
        case Init:
            postRotPosI+=QPoint(1,0);
            break;
        case R90:
            postRotPosI+=QPoint(0,1);
            break;
        case M180:
            postRotPosI+=QPoint(-1,0);
            break;
        case L90:
            postRotPosI+=QPoint(0,-1);
            break;
        default:
            break;
        }

        auto init = currentPiece->rotation;auto target = currentPiece->nextRotType(currentPiece->rotation);


        QVector<QPoint> tempPiecePoints = {};
        if(target == currentPiece->nextRotType(init)) {
            for(auto a : currentPiece->cells) {
                auto [rx,ry] = a.getrpos();
                tempPiecePoints.push_back(QPoint(-ry,rx));
            }
        } else {
            for(auto a : currentPiece->cells) {
                auto [rx,ry] = a.getrpos();
                tempPiecePoints.push_back(QPoint(ry,-rx));
            }
        }
        auto cpos = postRotPosI; //different from ZSLJT,rotation center is the geometry center

        QPair<RotationType,RotationType> request = {init,target};
        QVector<QPoint> requestTable = offsetTableI[request];
        for(auto &i : requestTable) {
            // i is the current offset
            if(!isCollision(tempPiecePoints,cpos+i)) {
                currentPiece->updatePoints(tempPiecePoints);
                currentPiece->pos = cpos+i;
                currentPiece->rotation = currentPiece->nextRotType(currentPiece->rotation);
                break;

            }
        }

    } else {
        auto [res,offset] = rotateAttemptRes(currentPiece->rotation,currentPiece->nextRotType(currentPiece->rotation));
        if(!res.isEmpty()) { // if success,then update points,pos,rotationType
            currentPiece->updatePoints(res);
            currentPiece->pos += offset;
            currentPiece->rotation = currentPiece->nextRotType(currentPiece->rotation);

        }
    }
    emit updateRequired();

}

QPair<QVector<QPoint>,QPoint> Engine::rotateAttemptRes(RotationType init, RotationType target) { // the res can be empty, which means no matching rotation
    QVector<QPoint> tempPiecePoints = {};
    if(target == currentPiece->nextRotType(init)) {
        for(auto a : currentPiece->cells) {
            auto [rx,ry] = a.getrpos();
            tempPiecePoints.push_back(QPoint(-ry,rx));
        }
    } else {
        for(auto a : currentPiece->cells) {
            auto [rx,ry] = a.getrpos();
            tempPiecePoints.push_back(QPoint(ry,-rx));
        }
    }
    auto cpos = currentPiece->pos;

    QPair<RotationType,RotationType> request = {init,target};
    QVector<QPoint> requestTable = offsetTableMain[request];
    for(auto &i : requestTable) {
        // i is the current offset
        if(!isCollision(tempPiecePoints,cpos+i)) {

            return {tempPiecePoints,i};

        }
    }
    //all failed
    return {{},{}};

}

void Engine::lock() {
    auto [points,pos] = currentPiece->getPieceLoc();
    QSet<int> rows = {};
    for(auto &point : points) {
        QPoint absPos = point + pos;
        int x = absPos.x();
        int y = absPos.y();
        rows.insert(y);
        board->getCell(y,x).fill(currentPiece->colorMap[currentPiece->type]);
    }
    examineAndClearLines(rows);


    *currentPiece=Piece(nexts.dequeue(),QPoint(1,4));
    emit updateRequired();
    return;
}

bool Engine::isFilledLine(int line) {
    for(int i = 0;i < 10;i++) {
        if(board->getCell(line,i).isEmpty()) return false;
    }
    return true;
}
//TODO: ADD row index check ,unify the name
void Engine::examineAndClearLines(QSet<int> lines) { //no same line
    QSet<int> filledlines = {};
    for(auto line:lines) {
        if(!isFilledLine(line)) continue;
        //else: clear
        filledlines.insert(line);
        for(int i = 0; i < 10; i++) {
            board->getCell(line,i).clear();
        }
    }
    int blanklen = filledlines.size();
    if(blanklen != 0) {
        int maxblankrow = *std::max_element(filledlines.begin(),filledlines.end());
        QVector<int> targetrows = {}; // must be in order

        for(int i = maxblankrow-1; i >= 0;i--) {
            if(!filledlines.contains(i)) targetrows.push_back(i);
        }
        //clear is over
        //if maxblankrow == 0,skip this statement
        int cnt = 0;
        for(auto i : targetrows) { //move from bottom
            for(int j = 0;j<10;j++) {
                board->getCell(maxblankrow-cnt,j).copyCellState(board->getCell(i,j));
                board->getCell(i,j).clear();
            }
            cnt++;
        }
    }

}

QPair<QPoint,QColor> Engine::getShadowPos(Piece* piece) {
    auto [points,pos] = piece->getPieceLoc();
    int x = pos.x();
    int y = pos.y();
    while(!isCollision(points, QPoint(x,y+1))) {
        y+=1;
    }
    return {{x,y},piece->colorMap[piece->type]};
}
