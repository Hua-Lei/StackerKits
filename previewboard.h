#ifndef PREVIEWBOARD_H
#define PREVIEWBOARD_H

#include <QWidget>
#include <QPainter>
#include "piece.h"
#include "engine.h"
#include "nextbag.h"

class PreviewBoard : public QWidget
{
    Q_OBJECT
public:
    explicit PreviewBoard(int previewNum, QWidget *parent = nullptr);
    void setPreviewBag(NextBag* srcpreviewBag);
    void setPreviewPiece(PieceType* previewPiece);

private:
    double cellLen=0;
    void paintEvent(QPaintEvent *) override;
    PieceType* previewPiece;
    NextBag* previewBag; // two modes
    int previewNum;
    QMap<PieceType,QString> colorMap = {{I,"cyan"},{O,"yellow"},{T,"purple"},{S,"green"},{Z,"red"},{L,"orange"},{J,"blue"}};

signals:
};

#endif // PREVIEWBOARD_H
