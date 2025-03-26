#include "previewboard.h"

PreviewBoard::PreviewBoard(int previewNum, QWidget *parent)
    : QWidget{parent},previewNum{previewNum}
{
    assert(previewNum>0);

}

void PreviewBoard::setPreviewBag(NextBag* srcpreviewBag) {
    previewBag = srcpreviewBag;
}
void PreviewBoard::setPreviewPiece(PieceType* srcpreviewPiece) {
    previewPiece = srcpreviewPiece;
}

void PreviewBoard::paintEvent(QPaintEvent *) {
    cellLen = this->geometry().width()/5.0; //width = 5 cellLens
    QSizeF sizef(cellLen,cellLen);

    QPainter painter(this);
    // QRectF rectBoarder(QPoint(0,0),QSizeF(cellLen*5,cellLen*3*previewNum));
    QPen pen;
    pen.setWidth(3);
    painter.setPen(pen);
    QMap<PieceType,QPoint> typeShift = {{I,QPoint(cellLen/2,0)},
                                          {O,QPoint(3*cellLen/2,cellLen/2)},
                                          {S,QPoint(cellLen,cellLen/2)},
                                          {Z,QPoint(cellLen,cellLen/2)},
                                          {L,QPoint(cellLen,cellLen/2)},
                                          {J,QPoint(cellLen,cellLen/2)},
                                          {T,QPoint(cellLen,cellLen/2)}};
    // painter.drawRect(rectBoarder);
    QRect borderRect = QRect(1, 1, width()-2, cellLen*3*previewNum);
    painter.drawRect(borderRect);
    pen.setWidth(0);
    QFont font("Calibri",9*width()/120,QFont::Bold,false);
    painter.setFont(font);
    if(previewNum == 1) {
        painter.drawText(borderRect,Qt::AlignHCenter ,"HOLD");
        if(*previewPiece!=Invaild) {
            Piece piece(*previewPiece,QPoint(1,1));
            auto [points,piecepos] = piece.getPieceLoc();
            for(auto &point : points) {
                QPointF pos = point + piecepos;
                pos.rx()*=cellLen;pos.ry()*=cellLen;
                pos.rx()+=typeShift[*previewPiece].rx();pos.ry()+=typeShift[*previewPiece].ry();
                QRectF rectf(pos,sizef);
                QColor color = colorMap[*previewPiece];
                painter.fillRect(rectf,color);
            }
        }
    } else {
        painter.drawText(borderRect,Qt::AlignHCenter ,"NEXT");
        for(int i = 0;i<previewNum;i++) {
            auto pieceType = previewBag->at(i);
            Piece piece(pieceType,QPoint(1,1));
            auto [points,piecepos] = piece.getPieceLoc();
            for(auto &point : points) {
                QPointF pos = point + piecepos;
                pos.rx()*=cellLen;pos.ry()*=cellLen;
                pos.rx()+=typeShift[pieceType].rx();pos.ry()+=typeShift[pieceType].ry();
                pos.ry() += i*cellLen*3;
                QRectF rectf(pos,sizef);
                QColor color = colorMap[pieceType];
                painter.fillRect(rectf,color);
        }
    }
    }
}
