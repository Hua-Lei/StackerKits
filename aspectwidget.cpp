#include "aspectwidget.h"

void AspectWidget::resizeEvent(QResizeEvent *event) {
    qDebug() << "resized";
    QSize newSize = event->size();
    double targetWidth, targetHeight;

    if (newSize.width() * aspectRatio <= newSize.height()) {
        targetWidth = newSize.width()*0.9;
        targetHeight = targetWidth / aspectRatio;
    } else {
        targetHeight = newSize.height()*0.9;
        targetWidth = targetHeight * aspectRatio;
    }



    double marginH = (newSize.width() - targetWidth) / 2;
    double marginV = (newSize.height() - targetHeight) / 2;

    this->layout()->setContentsMargins(marginH, marginV, marginH, marginV);

    QWidget::resizeEvent(event);
}
